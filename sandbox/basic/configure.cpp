//
// Created by ricka on 8/2/26.
//

#include "configure.hpp"

#include "scripts/scripts.hpp"

using namespace sandbox::basic;

static auto movable_player_quad(const sandbox::game& game) -> void;

auto sandbox::basic::configure(const game& game) -> void
{
    movable_player_quad(game);
}

static auto movable_player_quad(const sandbox::game& game) -> void
{
    NOI_ENGINE_REGISTER_SCRIPT(player_script);
    NOI_ENGINE_REGISTER_SCRIPT(camera_script);

    game.set_scene("assets/basic/scenes/main.scene.json");
}
