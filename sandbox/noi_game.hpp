//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <noi_engine/core/game.hpp>

class noi_game : public noi_engine::game
{
public:
	noi_game() : game("noi_game", 800, 600)
	{
	}
};