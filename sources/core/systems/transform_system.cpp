//
// Created by ricka on 8/2/26.
//

#include <noi_engine/core/systems/transform_system.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/world_matrix.hpp>
#include <noi_engine/core/components/dirty.hpp>

auto noi_engine::transform_system::sync(world& world) -> void
{
    for (const auto e : world.view<transform, dirty<transform>>())
    {
        world.get<world_matrix>(e).value = world_matrix::from(world.get<transform>(e));
        world.remove<dirty<transform>>(e);
    }
}
