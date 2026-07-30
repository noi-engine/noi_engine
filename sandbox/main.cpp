//
// Created by ricka on 2026-07-30.
//

#include "noi_game.hpp"
#include "scenes/test_scene.hpp"

auto main(const int argc, char* argv[]) -> int
{
	noi_game my_game;

	my_game.set_scene(std::make_unique<test_scene>());

	return my_game.run(argc, argv);
}