//
// Created by ricka on 8/23/26.
//

#pragma once

#include <string>
#include <glm/vec4.hpp>
#include <unordered_map>
#include <noi_engine/core/components/component.hpp>
#include <noi_engine/core/resources/resource_handle.hpp>

namespace noi_engine
{
    class shader;
    class texture;
    class resources;

    struct mesh_renderer_properties: component
    {
        std::unordered_map<std::string, float> m_parameters{};
        std::unordered_map<std::string, glm::vec4> m_colors{};
        std::unordered_map<std::string, bool> m_float_parameters{};
        std::unordered_map<std::string, resource_handle<texture>> m_textures{};

        auto set_parameter(std::string name, bool value) -> void;
        auto set_color(std::string name, glm::vec4 color) -> void;
        auto set_parameter(std::string name, float value) -> void;
        auto set_texture(std::string name, resource_handle<texture> texture) -> void;

        [[nodiscard]] auto is_empty() -> bool;

    };
}
