//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/model/mesh.hpp>
#include "noi_game.hpp"
#include "scenes/test_scene.hpp"

const auto vertex_shader_source = R"(
#version 330 core

layout(location = 0) in vec3 a_position;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    gl_Position =
        u_projection *
        u_view *
        u_model *
        vec4(a_position, 1.0);
}
)";

const auto fragment_shader_source = R"(
#version 330 core

out vec4 FragColor;

uniform vec4 u_color;

void main()
{
    FragColor = u_color;
}
)";

static auto create_cube_mesh() -> noi_engine::mesh
{
    std::vector<noi_engine::vertex> vertices
    {
        // Front (+Z)
        {.position = {-0.5f, -0.5f, 0.5f}, .normal = {0, 0, 1}, .uv = {0, 0}},
        {.position = {0.5f, -0.5f, 0.5f}, .normal = {0, 0, 1}, .uv = {1, 0}},
        {.position = {0.5f, 0.5f, 0.5f}, .normal = {0, 0, 1}, .uv = {1, 1}},
        {.position = {-0.5f, 0.5f, 0.5f}, .normal = {0, 0, 1}, .uv = {0, 1}},

        // Back (-Z)
        {.position = {0.5f, -0.5f, -0.5f}, .normal = {0, 0, -1}, .uv = {0, 0}},
        {.position = {-0.5f, -0.5f, -0.5f}, .normal = {0, 0, -1}, .uv = {1, 0}},
        {.position = {-0.5f, 0.5f, -0.5f}, .normal = {0, 0, -1}, .uv = {1, 1}},
        {.position = {0.5f, 0.5f, -0.5f}, .normal = {0, 0, -1}, .uv = {0, 1}},

        // Right (+X)
        {.position = {0.5f, -0.5f, 0.5f}, .normal = {1, 0, 0}, .uv = {0, 0}},
        {.position = {0.5f, -0.5f, -0.5f}, .normal = {1, 0, 0}, .uv = {1, 0}},
        {.position = {0.5f, 0.5f, -0.5f}, .normal = {1, 0, 0}, .uv = {1, 1}},
        {.position = {0.5f, 0.5f, 0.5f}, .normal = {1, 0, 0}, .uv = {0, 1}},

        // Left (-X)
        {.position = {-0.5f, -0.5f, -0.5f}, .normal = {-1, 0, 0}, .uv = {0, 0}},
        {.position = {-0.5f, -0.5f, 0.5f}, .normal = {-1, 0, 0}, .uv = {1, 0}},
        {.position = {-0.5f, 0.5f, 0.5f}, .normal = {-1, 0, 0}, .uv = {1, 1}},
        {.position = {-0.5f, 0.5f, -0.5f}, .normal = {-1, 0, 0}, .uv = {0, 1}},

        // Top (+Y)
        {.position = {-0.5f, 0.5f, 0.5f}, .normal = {0, 1, 0}, .uv = {0, 0}},
        {.position = {0.5f, 0.5f, 0.5f}, .normal = {0, 1, 0}, .uv = {1, 0}},
        {.position = {0.5f, 0.5f, -0.5f}, .normal = {0, 1, 0}, .uv = {1, 1}},
        {.position = {-0.5f, 0.5f, -0.5f}, .normal = {0, 1, 0}, .uv = {0, 1}},

        // Bottom (-Y)
        {.position = {-0.5f, -0.5f, -0.5f}, .normal = {0, -1, 0}, .uv = {0, 0}},
        {.position = {0.5f, -0.5f, -0.5f}, .normal = {0, -1, 0}, .uv = {1, 0}},
        {.position = {0.5f, -0.5f, 0.5f}, .normal = {0, -1, 0}, .uv = {1, 1}},
        {.position = {-0.5f, -0.5f, 0.5f}, .normal = {0, -1, 0}, .uv = {0, 1}},
    };

    std::vector<uint32_t> indices
    {
        // Front
        0, 1, 2,
        2, 3, 0,

        // Back
        4, 5, 6,
        6, 7, 4,

        // Right
        8, 9, 10,
        10, 11, 8,

        // Left
        12, 13, 14,
        14, 15, 12,

        // Top
        16, 17, 18,
        18, 19, 16,

        // Bottom
        20, 21, 22,
        22, 23, 20
    };

    noi_engine::mesh result(std::move(vertices), std::move(indices));
    result.upload();
    return result;
}

auto main(const int argc, char* argv[]) -> int
{
    noi_game my_game;

    auto first_scene = std::make_unique<test_scene>();
    auto& world = first_scene->get_world();

    my_game.set_scene(std::move(first_scene));

    auto& resources = my_game.resources();
    auto cube_mesh = resources.add(create_cube_mesh());

    auto color_shader = resources.add(
        noi_engine::shader(vertex_shader_source, fragment_shader_source)
    );

    noi_engine::material red_material;
    red_material.set_shader(color_shader);
    red_material.set_color("u_color", {1.0f, 0.0f, 0.0f, 1.0f});

    auto red_material_handle = resources.add(std::move(red_material));

    const auto cube = world.create_entity();

    world.add(cube, noi_engine::transform{
                  .position = {0.0f, 0.0f, -3.0f},
                  .rotation = {0.5f, 0.5f, 0.0f},
                  .scale = {0.8f, 0.8f, 0.8f}
              });
    world.add(
        cube,
        noi_engine::mesh_renderer
        {
            .m_mesh = cube_mesh,
            .m_material = red_material_handle
        }
    );

    return my_game.run(argc, argv);
}
