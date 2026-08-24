//
// Created by ricka on 8/23/26.
//

#include "builtin_shaders.hpp"
#include <memory>

namespace noi_engine
{
    static auto color_vert_src = R"(
#version 330 core

layout(location = 0) in vec3 a_position;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
}
)";

    static auto color_frag_src = R"(
#version 330 core

out vec4 FragColor;

uniform vec4 u_color;

void main()
{
    FragColor = u_color;
}
)";

    static auto texture_vert_src = R"(
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
    gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
}
)";

    static auto texture_frag_src = R"(
#version 330 core

in vec2 v_uv;

out vec4 FragColor;

uniform sampler2D u_texture;

void main()
{
    FragColor = texture(u_texture, v_uv);
}
)";

    static auto load_color_shader() -> std::unique_ptr<shader>
    {
        return std::make_unique<shader>(color_vert_src, color_frag_src);
    }

    static auto load_texture_shader() -> std::unique_ptr<shader>
    {
        return std::make_unique<shader>(texture_vert_src, texture_frag_src);
    }

    auto builtin_shaders::load(const std::string_view name, [[maybe_unused]] resources* resources) -> std::unique_ptr<shader>
    {
        static const std::unordered_map<std::string_view, std::function<std::unique_ptr<shader>()>> loaders = {
            {NOI_ENGINE_BUILTIN_COLOR_SHADER_NAME, &load_color_shader},
            {NOI_ENGINE_BUILTIN_TEXTURE_SHADER_NAME, &load_texture_shader}
        };

        if (const auto it = loaders.find(name); it != loaders.end())
        {
            return it->second();
        }

        return nullptr;
    }
} // namespace noi_engine
