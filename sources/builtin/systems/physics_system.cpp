//
// Created by ricka on 9/23/26.
//

#include <noi_engine/builtin/systems/physics_system.hpp>
#include <noi_engine/builtin/components/gravity.hpp>
#include <noi_engine/builtin/components/box_collider.hpp>
#include <noi_engine/builtin/signals/collision_signals.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/scene.hpp>
#include <glm/common.hpp>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>

// AABB physics: semi-implicit Euler integration for entities that opt in via `gravity`, then
// penetration resolution for entities that opt in via `box_collider`. Colliders are sorted along
// x and only neighbours are tested (sweep and prune), so the cost grows with the number of
// overlapping pairs, not with the square of the number of colliders. No restitution, friction or
// rotation. Entities without either component are never visited (see world::view<>).
namespace
{
    using namespace noi_engine;

    // Whether a body takes part in this step: always, unless an active area is given and the
    // body is outside it (and not always_active).
    auto is_active(world& world, const entity e, const view_area* area) -> bool
    {
        if (!area || world.has<always_active>(e))
            return true;

        const auto& t = world.get<transform>(e);
        const glm::vec2 half_size = world.has<box_collider>(e)
                                        ? world.get<box_collider>(e).half_extents
                                        : glm::vec2{t.scale.x, t.scale.y} * 0.5f;
        return area->overlaps({t.position.x, t.position.y}, half_size);
    }

    struct body
    {
        entity e;
        glm::vec2 centre; // collider centre, offset included
        glm::vec2 half;
        float left;
        float right;
    };

    auto make_body(world& world, const entity e) -> body
    {
        const auto& t = world.get<transform>(e);
        const auto& box = world.get<box_collider>(e);
        const glm::vec2 centre = glm::vec2{t.position.x, t.position.y} + box.offset;
        return {e, centre, box.half_extents, centre.x - box.half_extents.x, centre.x + box.half_extents.x};
    }

    auto layers_interact(const box_collider& a, const box_collider& b) -> bool
    {
        return (a.layer & b.mask) != 0u && (b.layer & a.mask) != 0u;
    }

    auto integrate(world& world, const float dt, const view_area* area) -> void
    {
        for (const auto e : world.view<transform, gravity>())
        {
            auto& g = world.get<gravity>(e);
            g.grounded = false;
            if (!g.enabled || !is_active(world, e, area))
                continue;

            g.velocity += g.acceleration * dt;

            auto& t = world.get<transform>(e);
            t.position.x += g.velocity.x * dt;
            t.position.y += g.velocity.y * dt;

            world.add_dirty_transform(e);
        }
    }

    // Moves a and/or b out of each other along the axis of least penetration (nothing moves for a
    // trigger) and records the contact when they overlap.
    auto resolve_pair(world& world, const body& a, const body& b,
                      std::vector<physics_system::contact>* contacts) -> void
    {
        const auto& box_a = world.get<box_collider>(a.e);
        const auto& box_b = world.get<box_collider>(b.e);

        if (!layers_interact(box_a, box_b))
            return;

        const bool trigger = box_a.is_trigger || box_b.is_trigger;
        const bool a_dynamic = !trigger && world.has<gravity>(a.e) && !box_a.is_static;
        const bool b_dynamic = !trigger && world.has<gravity>(b.e) && !box_b.is_static;

        // Two things that can't move don't interact, unless a trigger wants to be told.
        if (!trigger && !a_dynamic && !b_dynamic)
            return;

        const glm::vec2 delta = b.centre - a.centre;
        const glm::vec2 overlap = (a.half + b.half) - glm::abs(delta);
        if (overlap.x <= 0.0f || overlap.y <= 0.0f)
            return;

        if (contacts)
            contacts->push_back({a.e, b.e, trigger});

        if (trigger)
            return;

        const int axis = overlap.x < overlap.y ? 0 : 1;
        const float push = overlap[axis];
        const float sign = delta[axis] < 0.0f ? 1.0f : -1.0f;

        const float share_a = (a_dynamic && b_dynamic) ? push * 0.5f : (a_dynamic ? push : 0.0f);
        const float share_b = (a_dynamic && b_dynamic) ? push * 0.5f : (b_dynamic ? push : 0.0f);

        if (a_dynamic)
        {
            world.get<transform>(a.e).position[axis] += sign * share_a;
            auto& g = world.get<gravity>(a.e);
            g.velocity[axis] = 0.0f;
            // Pushed up along y: it stands on b.
            if (axis == 1 && sign > 0.0f)
                g.grounded = true;
            world.add_dirty_transform(a.e);
        }
        if (b_dynamic)
        {
            world.get<transform>(b.e).position[axis] -= sign * share_b;
            auto& g = world.get<gravity>(b.e);
            g.velocity[axis] = 0.0f;
            if (axis == 1 && sign < 0.0f)
                g.grounded = true;
            world.add_dirty_transform(b.e);
        }
    }

    auto collide(world& world, const view_area* area, std::vector<physics_system::contact>* contacts) -> void
    {
        std::vector<entity> colliders;
        for (const auto e : world.view<transform, box_collider>())
        {
            if (is_active(world, e, area))
                colliders.push_back(e);
        }

        // Sweep and prune along x: sorted by left edge, a box can only touch the following ones
        // whose left edge is before its right edge. Bodies move while pairs are resolved, so the
        // extents are read when a pair is tested.
        std::vector<body> bodies;
        bodies.reserve(colliders.size());
        for (const auto e : colliders)
            bodies.push_back(make_body(world, e));
        std::sort(bodies.begin(), bodies.end(), [](const body& a, const body& b) { return a.left < b.left; });

        for (std::size_t i = 0; i < bodies.size(); ++i)
        {
            const float reach = bodies[i].right;
            for (std::size_t j = i + 1; j < bodies.size() && bodies[j].left <= reach; ++j)
            {
                // Cheap rejection on y from the extents read when sorting (an earlier push moves a
                // body by less than the margin), before touching the world again.
                constexpr float margin = 0.5f;
                if (std::abs(bodies[i].centre.y - bodies[j].centre.y) > bodies[i].half.y + bodies[j].half.y + margin)
                    continue;

                // Refresh both: an earlier pair may have moved them.
                const auto a = make_body(world, bodies[i].e);
                const auto b = make_body(world, bodies[j].e);
                resolve_pair(world, a, b, contacts);
            }
        }
    }

    auto key_of(const entity a, const entity b) -> std::pair<std::uint64_t, std::uint64_t>
    {
        const auto first = pack(a);
        const auto second = pack(b);
        return first < second ? std::pair{first, second} : std::pair{second, first};
    }
}

auto noi_engine::physics_system::step(world& world, const float dt) -> void
{
    std::vector<contact> unused;
    step(world, dt, nullptr, unused);
}

auto noi_engine::physics_system::step(world& world, const float dt, const view_area& active_area) -> void
{
    std::vector<contact> unused;
    step(world, dt, &active_area, unused);
}

auto noi_engine::physics_system::step(world& world, const float dt, const view_area* active_area,
                                      std::vector<contact>& contacts) -> void
{
    contacts.clear();
    integrate(world, dt, active_area);
    collide(world, active_area, &contacts);
}

auto noi_engine::physics_system::on_update(const script_context& ctx, const float dt) -> void
{
    // Ticks aren't guaranteed to be regular (e.g. the editor only ticks on demand outside Play,
    // so the first tick after a scene loads can carry several real seconds of elapsed time).
    // step() integrates whatever dt it's given with no substepping, so an unclamped huge dt lets
    // a falling body's position jump further in one frame than a thin static collider is wide,
    // tunneling straight through it instead of colliding.
    constexpr float max_dt = 1.0f / 30.0f;
    const float clamped_dt = dt < max_dt ? dt : max_dt;

    auto& world = ctx.get_world();
    const auto camera = ctx.scene->get_camera_entity();
    view_area area;
    const bool use_area = world.has<culling>(camera) && !world.get<culling>(camera).simulate_offscreen &&
                          culling_area(world, camera, area);

    std::vector<contact> contacts;
    step(world, clamped_dt, use_area ? &area : nullptr, contacts);

    // Signals for pairs that started / stopped touching since the previous step.
    std::map<pair_key, bool> touching;
    for (const auto& c : contacts)
        touching[key_of(c.first, c.second)] = c.trigger;

    auto& bus = world.signals();
    for (const auto& c : contacts)
    {
        if (m_touching.contains(key_of(c.first, c.second)))
            continue;
        bus.emit<collision_begin>(collision_begin{c.first, c.second, c.trigger});
        bus.emit<collision_begin>(collision_begin{c.second, c.first, c.trigger});
    }

    for (const auto& [key, trigger] : m_touching)
    {
        if (touching.contains(key))
            continue;
        const auto first = unpack(key.first);
        const auto second = unpack(key.second);
        bus.emit<collision_end>(collision_end{first, second, trigger});
        bus.emit<collision_end>(collision_end{second, first, trigger});
    }

    m_touching = std::move(touching);
}
