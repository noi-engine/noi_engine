//
// Created by ricka on 8/1/26.
//

#pragma once

#include <string>
#include <unordered_map>
#include <glm/vec4.hpp>
#include <noi_engine/core/resources/resource_handle.hpp>

namespace noi_engine
{

    class shader;
    class texture;
    class resource_system;

    class material
    {
    public:
        auto set_shader(resource_handle<shader> shader) -> void;
        auto set_color(std::string name, glm::vec4 color) -> void;
        auto set_parameter(std::string name, float value) -> void;
        auto set_texture(std::string name, resource_handle<texture> texture) -> void;

        [[nodiscard]] auto shader() const noexcept -> resource_handle<shader>;

        auto apply(const noi_engine::shader &shader, resource_system &resources) -> void;

    private:
        resource_handle<class shader> m_shader{};
        std::unordered_map<std::string, float> m_parameters{};
        std::unordered_map<std::string, glm::vec4> m_colors{};
        std::unordered_map<std::string, resource_handle<texture>> m_textures{};
    };
}
