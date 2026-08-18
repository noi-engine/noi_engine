//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <noi_engine/core/sdl/sdl_game.hpp>

namespace sandbox
{
    class game : public noi_engine::sdl_game
    {
    public:
        game() : sdl_game("sandbox_game", 800, 600)
        {
        }
    };
}
