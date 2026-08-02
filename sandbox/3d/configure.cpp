//
// Created by ricka on 8/2/26.
//

#include "configure.hpp"

#include <memory>
#include <noi_engine/core/components/dirty.hpp>

#include "resources/meshes.hpp"
#include "resources/shaders.hpp"
#include "scenes/orbit_scene.hpp"

static auto red_cube_on_orbit(sandbox::game& game) -> void;
static auto obj_model_on_orbit_scene(sandbox::game& game) -> void;

auto sandbox::threed::configure(game& game) -> void
{
    //red_cube_on_orbit(game);
    obj_model_on_orbit_scene(game);
}

static auto red_cube_on_orbit(sandbox::game& game) -> void
{
    auto scene = std::make_unique<sandbox::threed::scenes::orbit_scene>();
    auto& world = scene->get_world();
    game.set_scene(std::move(scene));

    auto& resources = game.resources();
    const auto cube_mesh = resources.add(sandbox::threed::meshes::cube());
    const auto color_shader = resources.add(sandbox::threed::shaders::color_shader());

    noi_engine::material red_material;
    red_material.set_shader(color_shader);
    red_material.set_color("u_color", {1.0f, 0.0f, 0.0f, 1.0f});

    const auto red_material_handle = resources.add(std::move(red_material));
    const auto cube = world.create_entity();

    world.add(cube, noi_engine::transform{
                  .position = {0.0f, 0.0f, -3.0f},
                  .rotation = {0.5f, 0.5f, 0.0f},
                  .scale = {0.8f, 0.8f, 0.8f}
              });
    world.add(cube, noi_engine::world_matrix{});
    world.add(cube, noi_engine::dirty<noi_engine::transform>{});

    world.add(
        cube,
        noi_engine::mesh_renderer
        {
            .m_mesh = cube_mesh,
            .m_material = red_material_handle
        }
    );
}

static auto obj_model_on_orbit_scene(sandbox::game& game) -> void
{
    auto scene = std::make_unique<sandbox::threed::scenes::orbit_scene>();
    auto& world = scene->get_world();
    game.set_scene(std::move(scene));

    auto& resources = game.resources();
    const auto model_mesh = resources.add_mesh("assets/3d/models/suzanne.obj");
    const auto color_shader = resources.add(sandbox::threed::shaders::color_shader());

    noi_engine::material grey_material;
    grey_material.set_shader(color_shader);
    grey_material.set_color("u_color", {0.7f, 0.7f, 0.7f, 1.0f});

    const auto grey_material_handle = resources.add(std::move(grey_material));
    const auto model = world.create_entity();

    world.add(model, noi_engine::transform{
                  .position = {0.0f, 0.0f, 0.0f},
                  .scale = {1.0f, 1.0f, 1.0f}
              });
    world.add(model, noi_engine::world_matrix{});
    world.add(model, noi_engine::dirty<noi_engine::transform>{});

    world.add(
        model,
        noi_engine::mesh_renderer
        {
            .m_mesh = model_mesh,
            .m_material = grey_material_handle
        }
    );
}