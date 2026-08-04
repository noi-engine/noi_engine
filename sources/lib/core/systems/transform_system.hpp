//
// Created by ricka on 8/2/26.
//
#pragma once

#include <noi_engine/core/ecs/world.hpp>

namespace noi_engine
{
    class transform_system
    {
    public:
        transform_system() = delete;

        static auto sync(world& world) -> void;
    };
}