//
// Created by ricka on 8/2/26.
//

#include "configure.hpp"

#include <memory>
#include <noi_engine/core/components/dirty.hpp>
#include <noi_engine/core/components/mesh_renderer.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/world_matrix.hpp>
#include <noi_engine/core/model/material.hpp>

#include "components/player_controller.hpp"
#include "components/velocity.hpp"
#include "scenes/player_scene.hpp"

#include "../2d/resources/meshes.hpp"
#include "../2d/resources/shaders.hpp"

static auto movable_player_quad(sandbox::game& game) -> void;

auto sandbox::basic::configure(game& game) -> void
{
    movable_player_quad(game);
}

static auto movable_player_quad(sandbox::game& game) -> void
{
    auto scene = std::make_unique<sandbox::basic::player_scene>();
    auto& world = scene->get_world();
    game.set_scene(std::move(scene));

    auto& resources = game.resources();
    const auto quad_mesh = resources.add(sandbox::twod::meshes::quad());
    const auto color_shader = resources.add(sandbox::twod::shaders::color_shader());

    noi_engine::material green_material;
    green_material.set_shader(color_shader);
    green_material.set_color("u_color", {0.0f, 1.0f, 0.0f, 1.0f});

    const auto green_material_handle = resources.add(std::move(green_material));
    const auto player = world.create_entity();

    world.add(player, noi_engine::transform{.scale = {0.8f, 0.8f, 0.8f}});
    world.add(player, noi_engine::world_matrix{});
    world.add(player, noi_engine::dirty<noi_engine::transform>{});
    world.add(player, sandbox::basic::velocity{});
    world.add(player, sandbox::basic::player_controller{.speed = 3.0f});

    world.add(
        player,
        noi_engine::mesh_renderer
        {
            .m_mesh = quad_mesh,
            .m_material = green_material_handle
        }
    );
}
