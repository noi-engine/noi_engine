//
// Created by ricka on 8/2/26.
//

#include "configure.hpp"

#include <noi_engine/core/resources/resources.hpp>
#include <noi_engine/core/scene.hpp>
#include <utility>

#include "systems/bounds_system.hpp"
#include "systems/entity_counter_system.hpp"
#include "systems/fps_counter_system.hpp"

using namespace sandbox::basic;

static auto movable_player_quad(const sandbox::game& game) -> void;

auto sandbox::basic::configure(const game& game) -> void
{
    movable_player_quad(game);
}

static auto movable_player_quad(const sandbox::game& game) -> void
{
    auto scene = game.resources().load_scene("assets/basic/scenes/main.scene.json");

    scene->add_system<bounds_system>();
    scene->add_system_after<bounds_system, entity_counter_system>();
    scene->add_system<fps_counter_system>();

    game.set_scene(std::move(scene));
}
