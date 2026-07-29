//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/game.hpp>

auto main(const int argc, char* argv[]) -> int
{
	noi_engine::game my_game("BestGame", 700, 600);

	return my_game.run(argc, argv);
}
