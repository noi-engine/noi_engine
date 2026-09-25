//
// Created by ricka on 9/23/26.
//

#include "physics_system.hpp"
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/gravity.hpp>
#include <noi_engine/core/components/box_collider.hpp>
#include <glm/common.hpp>
#include <vector>

// A minimal, first-pass AABB physics step: semi-implicit Euler integration for entities that
// opt in via `gravity`, then pairwise penetration resolution for entities that opt in via
// `box_collider`. No broad-phase, no restitution/friction/rotation - entities without either
// component are never visited (see world::view<>), so this costs nothing when unused.
auto noi_engine::physics_system::step(world& world, const float dt) -> void
{
    for (const auto e : world.view<transform, gravity>())
    {
        auto& g = world.get<gravity>(e);
        if (!g.enabled)
            continue;

        g.velocity += g.acceleration * dt;

        auto& t = world.get<transform>(e);
        t.position.x += g.velocity.x * dt;
        t.position.y += g.velocity.y * dt;

        world.add_dirty_transform(e);
    }

    std::vector<entity> colliders;
    for (const auto e : world.view<transform, box_collider>())
        colliders.push_back(e);

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

auto noi_engine::physics_system::on_update(const script_context& ctx, const float dt) -> void
{
    step(ctx.get_world(), dt);
}
