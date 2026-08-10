//
// Created by ricka on 8/2/26.
//

#include "configure.hpp"

#include <memory>
#include <noi_engine/core/scripts/script.hpp>

#include "scenes/player_scene.hpp"

using namespace sandbox::basic;

static auto movable_player_quad(sandbox::game& game) -> void;

auto sandbox::basic::configure(game& game) -> void
{
    movable_player_quad(game);
}

static auto movable_player_quad(sandbox::game& game) -> void
{
    game.set_scene(std::move(std::make_unique<player_scene>()));
}
