//
// Created by ricka on 8/9/26.
//

#pragma once

#include <noi_engine/core/ecs/world.hpp>

namespace noi_engine
{
    struct action_context
    {
        float dt{};
        world* world{nullptr};

        [[nodiscard]] static auto from(const float dt, noi_engine::world* world) -> action_context
        {
            return action_context{.dt = dt, .world = world};
        }
    };
}
