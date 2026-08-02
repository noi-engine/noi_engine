//
// Created by ricka on 2026-07-30.
//

#include "sandbox_game.hpp"
#include "3d/configure.hpp"

auto main(const int argc, char* argv[]) -> int
{
    sandbox::game my_game;

    sandbox::configure_3d(my_game);

    return my_game.run(argc, argv);
}
