//
// Created by ricka on 8/9/26.
//

#pragma once

#include <noi_engine/core/ecs/world.hpp>

namespace noi_engine
{
    class script_system
    {
    public:
        script_system() = delete;

        static auto before_update(world& world, float dt) -> void;
        static auto update(world& world, float dt) -> void;
        static auto after_update(world& world, float dt) -> void;
        static auto before_render(world& world) -> void;
        static auto after_render(world& world) -> void;
        static auto destroy(world& world, entity target) -> void;
    };
}
