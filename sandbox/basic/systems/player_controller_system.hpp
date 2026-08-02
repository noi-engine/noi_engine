//
// Created by ricka on 8/2/26.
//

#pragma once

#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/input/input_state.hpp>

namespace sandbox::basic
{
    class player_controller_system
    {
    public:
        player_controller_system() = delete;

        static auto update(noi_engine::world& world, const noi_engine::input_state& input) -> void;
    };
}
