//
// Created by ricka on 8/1/26.
//

#include "../glad/glad.h"
#include <stdexcept>
#include <vector>
#include <noi_engine/core/model/shader.hpp>

namespace
{
    auto compile(const GLenum type, const std::string& src) -> uint32_t
    {
        const auto id = glCreateShader(type);
        const auto* c_src = src.c_str();

        glShaderSource(id, 1, &c_src, nullptr);
        glCompileShader(id);

        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);

        if (success == 0)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> log(length);
            glGetShaderInfoLog(id, length, nullptr, log.data());
            throw std::runtime_error(std::string(log.begin(), log.end()));
        }

        return id;
    }
}

noi_engine::shader::shader(const std::string& vertex_src, const std::string& fragment_src)
{
    const auto vertex = compile(GL_VERTEX_SHADER, vertex_src);
    const auto fragment = compile(GL_FRAGMENT_SHADER, fragment_src);

    m_program = glCreateProgram();
    glAttachShader(m_program, vertex);
    glAttachShader(m_program, fragment);
    glLinkProgram(m_program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

noi_engine::shader::~shader()
{
    if (m_program != 0)
    {
        glDeleteProgram(m_program);
    }
}

noi_engine::shader::shader(shader&& other) noexcept : m_program(other.m_program)
{
    other.m_program = 0;
}

auto noi_engine::shader::operator=(shader&& other) noexcept -> shader&
{
    if (this == &other)
        return *this;

    m_program = other.m_program;
    other.m_program = 0;

    return *this;
}

auto noi_engine::shader::use() const -> void
{
    glUseProgram(m_program);
}

auto noi_engine::shader::set_mat4(const std::string& name, const glm::mat4& value) const -> void
{
    const auto location = glGetUniformLocation(m_program, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

auto noi_engine::shader::set_int(const std::string& name, const int value) const -> void
{
    const auto location = glGetUniformLocation(m_program, name.c_str());
    glUniform1i(location, value);
}
