//
// Created by ricka on 8/9/26.
//

#include <SDL2/SDL.h>
#include <noi_engine/sdl/sdl_game.hpp>

#include "../core/timer.hpp"
#include "../core/glad/glad.h"
#include "../core/frame_limiter.hpp"
#include "../core/sdl_event_processor.hpp"

auto noi_engine::sdl_game::process_events() -> void
{
    this->m_input.begin_frame();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            m_running = false;
            return;
        }

        if (event.type == SDL_WINDOWEVENT &&
            (event.window.event == SDL_WINDOWEVENT_RESIZED ||
                event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED))
        {
            glViewport(0, 0, event.window.data1, event.window.data2);
            this->m_scene_manager.on_resize(event.window.data1, event.window.data2);
        }

        sdl_event_processor::process(event, this->m_input);
    }
}

noi_engine::sdl_game::sdl_game(const std::string& title, int width, int height, const sdl_game_conf& game_conf) :
    game(game_conf)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        throw std::runtime_error("Cannot init sdl");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    this->m_conf = game_conf;
    this->m_window = std::make_unique<sdl_window>(title, width, height);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

auto noi_engine::sdl_game::run([[maybe_unused]] int argc, [[maybe_unused]] char** argv) -> int
{
    timer timer;
    frame_limiter frame_limiter(m_conf.max_fps);
    m_running = true;

    while (m_running)
    {
        frame_limiter.begin();

        const float dt = timer.tick();

        this->process_events();
        this->update(dt);

        renderer::begin_frame();
        render();
        renderer::end_frame();

        this->m_window->swap_buffers();

        frame_limiter.end();
    }

    return 0;
}

noi_engine::sdl_game::~sdl_game()
{
    SDL_Quit();
}

auto noi_engine::sdl_game::get_window() -> sdl_window&
{
    return *this->m_window;
}

auto noi_engine::sdl_game::get_window() const -> const sdl_window&
{
    return *this->m_window;
}
