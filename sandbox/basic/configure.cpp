//
// Created by ricka on 8/2/26.
//

#include "configure.hpp"

using namespace sandbox::basic;

static auto movable_player_quad(const sandbox::game& game) -> void;

auto sandbox::basic::configure(const game& game) -> void
{
    movable_player_quad(game);
}

static auto movable_player_quad(const sandbox::game& game) -> void
{
    game.set_scene("assets/basic/scenes/main.scene.json");
}
