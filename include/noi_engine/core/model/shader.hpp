//
// Created by ricka on 8/1/26.
//

#pragma once

#include <cstdint>
#include <string>
#include <glm/mat4x4.hpp>

namespace noi_engine
{
    class shader
    {
        uint32_t m_program{ 0 };

    public:
        explicit shader(const std::string& vertex_src, const std::string& fragment_src);

        ~shader();

        shader(const shader&) = delete;

        auto operator=(const shader&) -> shader& = delete;

        shader(shader&& other) noexcept;

        auto operator=(shader&& other) noexcept -> shader&;

        auto use() const -> void;

        auto set_mat4(const std::string& name, const glm::mat4& value) const -> void;

        auto set_int(const std::string& name, int value) const -> void;
    };
}