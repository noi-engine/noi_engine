//
// Created by ricka on 8/2/26.
//

#include <noi_engine/core/components/dirty.hpp>
#include <noi_engine/core/components/transform.hpp>

#include "movement_system.hpp"
#include "../components/velocity.hpp"

auto sandbox::basic::movement_system::update(noi_engine::world& world, const float dt) -> void
{
    for (const auto e : world.view<noi_engine::transform, velocity>())
    {
        const auto& vel = world.get<velocity>(e);

        if (vel.value == glm::vec3{0.0f})
            continue;

        auto& tr = world.get<noi_engine::transform>(e);
        tr.position += vel.value * dt;

        world.add(e, noi_engine::dirty<noi_engine::transform>{});
    }
}
