//
// Created by ricka on 8/2/26.
//

#include "configure.hpp"

#include <memory>
#include <noi_engine/core/scripts/script.hpp>
#include <noi_engine/core/components/script_component.hpp>

#include "scripts/scripts.hpp"
#include "scenes/player_scene.hpp"
#include "../2d/resources/meshes.hpp"
#include "../2d/resources/shaders.hpp"

using namespace sandbox::basic;

static auto movable_player_quad(sandbox::game& game) -> void;

auto sandbox::basic::configure(game& game) -> void
{
    movable_player_quad(game);
}

static auto movable_player_quad(sandbox::game& game) -> void
{
    auto scene = std::make_unique<player_scene>();
    auto& world = scene->get_world();
    const auto camera = scene->get_camera_entity();

    auto& resources = game.resources();
    const auto quad_mesh = resources.add(sandbox::twod::meshes::quad());
    const auto color_shader = resources.add(sandbox::twod::shaders::color_shader());

    const auto background = world.create_entity();
    world.add(background, noi_engine::script_component{
                  .instance = std::make_shared<background_script>(
                      resources,
                      quad_mesh,
                      color_shader
                  )
              });

    const auto player = world.create_entity();
    world.add(player, noi_engine::script_component{
                  .instance = std::make_shared<player_script>(
                      resources,
                      quad_mesh,
                      color_shader
                  )
              });

    world.add(camera, noi_engine::script_component{.instance = std::make_shared<camera_script>(player)});
    game.set_scene(std::move(scene));
}
