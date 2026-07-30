//
// Created by ricka on 2026-07-30.
//

#include <SDL2/SDL.h>
#include <noi_engine/core/game.hpp>
#include <noi_engine/core/timer.hpp>
#include <stdexcept>

#include "glad/glad.h"

auto noi_engine::game::render() -> void
{
}

auto noi_engine::game::process_events() -> void
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			m_running = false;
		}
	}
}

auto noi_engine::game::update(float dt) -> void
{
}

noi_engine::game::game(const std::string& title, int width, int height,
                       const game_conf& conf)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		throw std::runtime_error("Cannot init sdl");
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
	                    SDL_GL_CONTEXT_PROFILE_CORE);

	this->m_window = std::make_unique<window>(title, width, height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

noi_engine::game::~game()
{
	SDL_Quit();
}

auto noi_engine::game::get_window() -> window&
{
	return *this->m_window;
}

auto noi_engine::game::get_window() const -> const window&
{
	return *this->m_window;
}

auto noi_engine::game::run(const int argc, char** argv) -> int
{
	timer timer;
	m_running = true;

	while (m_running)
	{
		const float dt = timer.tick();

		process_events();

		update(dt);

		render();
	}

	return 0;
}