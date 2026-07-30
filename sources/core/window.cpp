//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/window.hpp>
#include <SDL2/SDL.h>
#include <gtest/internal/gtest-param-util.h>

#include <stdexcept>

#include "glad/glad.h"

noi_engine::window::~window()
{
	if (this->gl_context != nullptr)
	{
		SDL_GL_DeleteContext(this->gl_context);
	}

	if (this->sdl_window != nullptr)
	{
		SDL_DestroyWindow(this->sdl_window);
	}
}

noi_engine::window::window(const std::string& title, int width, int height,
                           const window_conf& conf)
{
	constexpr auto dpi_scale = 1;
	const auto window_width = static_cast<int>(
		static_cast<float>(width) * dpi_scale);
	const auto window_height = static_cast<int>(
		static_cast<float>(height) * dpi_scale);

	this->sdl_window = SDL_CreateWindow(title.c_str(),
	                                    SDL_WINDOWPOS_CENTERED,
	                                    SDL_WINDOWPOS_CENTERED,
	                                    window_width,
	                                    window_height,
	                                    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	                                    | SDL_WINDOW_SHOWN |
	                                    SDL_WINDOW_ALLOW_HIGHDPI);

	this->gl_context = SDL_GL_CreateContext(this->sdl_window);
	SDL_GL_MakeCurrent(this->sdl_window, this->gl_context);

	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
	{
		SDL_GL_DeleteContext(this->gl_context);
		SDL_DestroyWindow(this->sdl_window);
		throw std::runtime_error("Failed to initialize GLAD");
	}
}

auto noi_engine::window::get_size() const -> size_2d
{
	int width, height;
	SDL_GetWindowSize(this->sdl_window, &width, &height);
	return size_2d{ width, height };
}

auto noi_engine::window::swap_buffers() -> void
{
	SDL_GL_SwapWindow(this->sdl_window);
}