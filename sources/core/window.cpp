//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/window.hpp>
#include <SDL2/SDL.h>
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
		SDL_DestroyWindow(this->sdl_window);
		SDL_GL_DeleteContext(this->gl_context);
		throw std::runtime_error("Failed to initialize GLAD");
	}
}