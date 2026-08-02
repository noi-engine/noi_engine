//
// Created by ricka on 2026-07-30.
//

#include "sandbox_game.hpp"
#include "2d/configure.hpp"
#include "3d/configure.hpp"
#include "basic/configure.hpp"

auto main(const int argc, char* argv[]) -> int
{
    sandbox::game my_game;

    //sandbox::twod::configure(my_game);
    //sandbox::threed::configure(my_game);
    sandbox::basic::configure(my_game);

    return my_game.run(argc, argv);
}
