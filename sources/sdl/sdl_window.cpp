//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/game.hpp>
#include <noi_engine/sdl/sdl_window.hpp>

#include <SDL2/SDL.h>
#include <stdexcept>
#include <gtest/internal/gtest-param-util.h>

noi_engine::sdl_window::~sdl_window()
{
    if (this->gl_context != nullptr)
    {
        SDL_GL_DeleteContext(this->gl_context);
    }

    if (this->sdl_raw_window != nullptr)
    {
        SDL_DestroyWindow(this->sdl_raw_window);
    }
}

noi_engine::sdl_window::sdl_window(const std::string& title, const int width, const int height,
                                   [[maybe_unused]] const sdl_window_conf& conf)
{
    constexpr auto dpi_scale = 1;
    const auto window_width = static_cast<int>(
        static_cast<float>(width) * dpi_scale);
    const auto window_height = static_cast<int>(
        static_cast<float>(height) * dpi_scale);

    this->sdl_raw_window = SDL_CreateWindow(title.c_str(),
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            window_width,
                                            window_height,
                                            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
                                            | SDL_WINDOW_SHOWN |
                                            SDL_WINDOW_ALLOW_HIGHDPI);

    this->gl_context = SDL_GL_CreateContext(this->sdl_raw_window);
    SDL_GL_MakeCurrent(this->sdl_raw_window, this->gl_context);

    try
    {
        game::init(SDL_GL_GetProcAddress);
    }
    catch ([[maybe_unused]] std::runtime_error& e)
    {
        SDL_GL_DeleteContext(this->gl_context);
        SDL_DestroyWindow(this->sdl_raw_window);
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

auto noi_engine::sdl_window::get_size() const -> glm::vec2
{
    int width, height;
    SDL_GetWindowSize(this->sdl_raw_window, &width, &height);
    return glm::vec2{width, height};
}

auto noi_engine::sdl_window::swap_buffers() -> void
{
    SDL_GL_SwapWindow(this->sdl_raw_window);
}
