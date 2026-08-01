//
// Created by ricka on 8/1/26.
//

#include <utility>
#include <noi_engine/core/model/material.hpp>

namespace noi_engine
{
    auto material::set_shader(resource_handle<noi_engine::shader> shader) -> void
    {
        m_shader = shader;
    }

    auto material::set_color(std::string name, glm::vec4 color) -> void
    {
        m_colors[std::move(name)] = color;
    }

    auto material::set_parameter(std::string name, float value) -> void
    {
        m_parameters[std::move(name)] = value;
    }

    auto material::set_texture(std::string name,resource_handle<texture> texture) -> void
    {
        m_textures[std::move(name)] = texture;
    }

    auto material::shader() const noexcept -> resource_handle<noi_engine::shader>
    {
        return m_shader;
    }
}