//
// Created by ricka on 8/2/26.
//

#include "configure.hpp"

#include <memory>
#include <noi_engine/core/components/dirty.hpp>

#include "resources/meshes.hpp"
#include "resources/shaders.hpp"
#include "scenes/basic_scene.hpp"

static auto blue_cube_on_basic_scene(sandbox::game& game) -> void;

auto sandbox::twod::configure(game& game) -> void
{
    blue_cube_on_basic_scene(game);
}

static auto blue_cube_on_basic_scene(sandbox::game& game) -> void
{
    auto scene = std::make_unique<sandbox::twod::scenes::basic_scene>();
    auto& world = scene->get_world();
    game.set_scene(std::move(scene));

    auto& resources = game.resources();
    const auto quad_mesh = resources.add(sandbox::twod::meshes::quad());
    const auto color_shader = resources.add(sandbox::twod::shaders::color_shader());

    noi_engine::material blue_material;
    blue_material.set_shader(color_shader);
    blue_material.set_color("u_color", {0.0f, 0.0f, 1.0f, 1.0f});

    const auto blue_material_handle = resources.add(std::move(blue_material));
    const auto cube = world.create_entity();

    world.add(cube, noi_engine::transform{.scale = {0.8f, 0.8f, 0.8f}});
    world.add(cube, noi_engine::world_matrix{});
    world.add(cube, noi_engine::dirty<noi_engine::transform>{});

    world.add(
        cube,
        noi_engine::mesh_renderer
        {
            .m_mesh = quad_mesh,
            .m_material = blue_material_handle
        }
    );
}
