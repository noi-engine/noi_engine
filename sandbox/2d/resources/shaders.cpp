//
// Created by ricka on 8/2/26.
//

#include "shaders.hpp"

auto sandbox::twod::shaders::color_shader() -> noi_engine::shader
{
    constexpr auto vertex_shader_source = R"(
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

    constexpr auto fragment_shader_source = R"(
#version 330 core

out vec4 FragColor;

uniform vec4 u_color;

void main()
{
    FragColor = u_color;
}
)";

    return noi_engine::shader(vertex_shader_source, fragment_shader_source);
}

auto sandbox::twod::shaders::texture_shader() -> noi_engine::shader
{
    constexpr auto vertex_shader_source = R"(
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec2 a_uv;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 v_uv;

void main()
{
    v_uv = a_uv;

    gl_Position =
        u_projection *
        u_view *
        u_model *
        vec4(a_position, 1.0);
}
)";


    constexpr auto fragment_shader_source = R"(
#version 330 core

in vec2 v_uv;

out vec4 FragColor;

uniform sampler2D u_texture;

void main()
{
    FragColor = texture(u_texture, v_uv);
}
)";

    return noi_engine::shader(vertex_shader_source, fragment_shader_source);
}
