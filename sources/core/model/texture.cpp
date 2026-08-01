//
// Created by ricka on 8/1/26.
//

#include <SDL_surface.h>

#include "../glad/glad.h"
#include <stdexcept>
#include <noi_engine/core/model/texture.hpp>
#include <SDL2/SDL_image.h>

static auto from_surface(GLuint &id, const SDL_Surface *surface) -> void
{
    if (!surface)
    {
        throw std::runtime_error("from_surface received null surface");
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    const GLint format = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D,
        0,
        format,
        surface->w,
        surface->h,
        0,
        format,
        GL_UNSIGNED_BYTE,
        surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

noi_engine::texture::texture(const std::string& path)
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface)
    {
        throw std::runtime_error("Failed to load image: " + path);
    }

    GLuint id;
    from_surface(id, surface);

    this->m_id = id;
    this->m_width = surface->w;
    this->m_height = surface->h;

    SDL_FreeSurface(surface);
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
