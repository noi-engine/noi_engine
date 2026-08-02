//
// Created by ricka on 8/2/26.
//

#pragma once

#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/input/input_state.hpp>

namespace noi_engine
{
    class camera_2d_debug_controller_system
    {
    public:
        camera_2d_debug_controller_system() = delete;

        static auto update(world& world, entity camera_entity, const input_state& input) -> void;
    };
}
