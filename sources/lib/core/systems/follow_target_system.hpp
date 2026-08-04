//
// Created by ricka on 8/2/26.
//

#pragma once

#include <noi_engine/core/ecs/world.hpp>

namespace noi_engine
{
    class follow_target_system
    {
    public:
        follow_target_system() = delete;

        static auto update(world& world, float dt) -> void;
    };
}
