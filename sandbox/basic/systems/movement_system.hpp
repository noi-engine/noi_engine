//
// Created by ricka on 8/2/26.
//

#pragma once

#include <noi_engine/core/ecs/world.hpp>

namespace sandbox::basic
{
    class movement_system
    {
    public:
        movement_system() = delete;

        static auto update(noi_engine::world& world, float dt) -> void;
    };
}
