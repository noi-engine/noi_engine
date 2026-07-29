//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <SDL2/SDL_video.h>

#include <string>

namespace noi_engine
{
	struct window_conf
	{
	};

	class window
	{
	protected:
		SDL_Window* sdl_window = nullptr;
		SDL_GLContext gl_context = nullptr;

	public:
		virtual ~window();

		explicit window(const std::string& title, int width, int height,
		                const window_conf& conf = window_conf());
	};
}