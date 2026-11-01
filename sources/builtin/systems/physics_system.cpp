//
// Created by ricka on 9/23/26.
//

#include <noi_engine/builtin/systems/physics_system.hpp>
#include <noi_engine/builtin/components/gravity.hpp>
#include <noi_engine/builtin/components/box_collider.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/scene.hpp>
#include <glm/common.hpp>
#include <vector>

// A minimal, first-pass AABB physics step: semi-implicit Euler integration for entities that
// opt in via `gravity`, then pairwise penetration resolution for entities that opt in via
// `box_collider`. No broad-phase, no restitution/friction/rotation - entities without either
// component are never visited (see world::view<>), so this costs nothing when unused.
namespace
{
    // Whether a body takes part in this step: always, unless an active area is given and the
    // body is outside it (and not always_active).
    auto is_active(noi_engine::world& world, const noi_engine::entity e, const noi_engine::view_area* area) -> bool
    {
        if (!area || world.has<noi_engine::always_active>(e))
            return true;

        const auto& t = world.get<noi_engine::transform>(e);
        const glm::vec2 half_size = world.has<noi_engine::box_collider>(e)
                                        ? world.get<noi_engine::box_collider>(e).half_extents
                                        : glm::vec2{t.scale.x, t.scale.y} * 0.5f;
        return area->overlaps({t.position.x, t.position.y}, half_size);
    }

    auto step_bodies(noi_engine::world& world, const float dt, const noi_engine::view_area* area) -> void;
}

auto noi_engine::physics_system::step(world& world, const float dt) -> void
{
    step_bodies(world, dt, nullptr);
}

auto noi_engine::physics_system::step(world& world, const float dt, const view_area& active_area) -> void
{
    step_bodies(world, dt, &active_area);
}

namespace
{
using namespace noi_engine;

auto step_bodies(world& world, const float dt, const view_area* area) -> void
{
    for (const auto e : world.view<transform, gravity>())
    {
        auto& g = world.get<gravity>(e);
        if (!g.enabled || !is_active(world, e, area))
            continue;

        g.velocity += g.acceleration * dt;

        auto& t = world.get<transform>(e);
        t.position.x += g.velocity.x * dt;
        t.position.y += g.velocity.y * dt;

        world.add_dirty_transform(e);
    }

    std::vector<entity> colliders;
    for (const auto e : world.view<transform, box_collider>())
    {
        if (is_active(world, e, area))
            colliders.push_back(e);
    }

    for (size_t i = 0; i < colliders.size(); ++i)
    {
        for (size_t j = i + 1; j < colliders.size(); ++j)
        {
            const auto a = colliders[i];
            const auto b = colliders[j];

            const auto& box_a = world.get<box_collider>(a);
            const auto& box_b = world.get<box_collider>(b);

            const bool a_dynamic = world.has<gravity>(a) && !box_a.is_static;
            const bool b_dynamic = world.has<gravity>(b) && !box_b.is_static;
            if (!a_dynamic && !b_dynamic)
                continue;

            auto& transform_a = world.get<transform>(a);
            auto& transform_b = world.get<transform>(b);

            const glm::vec2 center_a{transform_a.position.x, transform_a.position.y};
            const glm::vec2 center_b{transform_b.position.x, transform_b.position.y};
            const glm::vec2 delta = center_b - center_a;
            const glm::vec2 overlap = (box_a.half_extents + box_b.half_extents) - glm::abs(delta);

            if (overlap.x <= 0.0f || overlap.y <= 0.0f)
                continue;

            const int axis = overlap.x < overlap.y ? 0 : 1;
            const float push = overlap[axis];
            const float sign = delta[axis] < 0.0f ? 1.0f : -1.0f;

            const float share_a = (a_dynamic && b_dynamic) ? push * 0.5f : (a_dynamic ? push : 0.0f);
            const float share_b = (a_dynamic && b_dynamic) ? push * 0.5f : (b_dynamic ? push : 0.0f);

            if (a_dynamic)
            {
                transform_a.position[axis] += sign * share_a;
                world.get<gravity>(a).velocity[axis] = 0.0f;
                world.add_dirty_transform(a);
            }
            if (b_dynamic)
            {
                transform_b.position[axis] -= sign * share_b;
                world.get<gravity>(b).velocity[axis] = 0.0f;
                world.add_dirty_transform(b);
            }
        }
    }
}

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
    if (world.has<culling>(camera) && !world.get<culling>(camera).simulate_offscreen &&
        culling_area(world, camera, area))
    {
        step(world, clamped_dt, area);
        return;
    }
    step(world, clamped_dt);
}
