//
// Created by ricka on 8/1/26.
//

#include "../glad/glad.h"
#include <noi_engine/core/model/texture.hpp>

noi_engine::texture::texture(const int width, const int height, const std::span<const std::byte> pixels)
    : m_width(width),
      m_height(height)
{
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        pixels.data()
    );

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

noi_engine::texture::~texture()
{
    if (m_id != 0)
    {
        glDeleteTextures(1, &m_id);
    }
}

noi_engine::texture::texture(texture&& other) noexcept
    : m_id(other.m_id), m_width(other.m_width), m_height(other.m_height)
{
    other.m_id = 0;
}

auto noi_engine::texture::operator=(texture&& other) noexcept -> texture&
{
    if (this == &other)
        return *this;

    m_id = other.m_id;
    m_width = other.m_width;
    m_height = other.m_height;

    other.m_id = 0;

    return *this;
}

auto noi_engine::texture::bind(const uint32_t slot) const -> void
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

auto noi_engine::texture::id() const noexcept -> uint32_t
{
    return m_id;
}

auto noi_engine::texture::width() const noexcept -> int
{
    return m_width;
}

auto noi_engine::texture::height() const noexcept -> int
{
    return m_height;
}
