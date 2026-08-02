//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <noi_engine/core/game.hpp>

namespace sandbox
{
    class game : public noi_engine::game
    {
    public:
        game() : noi_engine::game("sandbox_game", 800, 600)
        {
        }
    };
}
