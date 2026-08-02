//
// Created by ricka on 2026-07-30.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <noi_engine/core/game.hpp>
#include <noi_engine/core/timer.hpp>
#include <stdexcept>

#include "frame_limiter.hpp"
#include "glad/glad.h"

auto noi_engine::game::render() -> void
{
    this->m_scene_manager.render(*this->m_renderer);
}

auto noi_engine::game::process_events() -> void
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
            m_scene_manager.on_resize(event.window.data1, event.window.data2);
        }

        this->m_input.process_event(event);
        this->m_input.process_event(event);
    }
}

auto noi_engine::game::update(const float dt) -> void
{
    this->m_scene_manager.update(dt, m_input);
}

noi_engine::game::game(const std::string& title, int width, int height,
                       const game_conf& conf)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        throw std::runtime_error("Cannot init sdl");
    }

    if ((IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) & (IMG_INIT_JPG | IMG_INIT_PNG)) == 0)
    {
        SDL_Quit();
        throw std::runtime_error("Cannot init sdl_image");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    this->m_window = std::make_unique<window>(title, width, height);
    this->m_renderer = std::make_unique<renderer>(this->m_resources);

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    this->m_conf = conf;
    if (this->m_conf.v_sync)
    {
        SDL_GL_SetSwapInterval(1);
    }
}

noi_engine::game::~game()
{
    IMG_Quit();
    SDL_Quit();
}

auto noi_engine::game::set_scene(std::unique_ptr<scene> scene) -> void
{
    this->m_scene_manager.set_scene(std::move(scene));
}

auto noi_engine::game::get_window() -> window&
{
    return *this->m_window;
}

auto noi_engine::game::get_window() const -> const window&
{
    return *this->m_window;
}

auto noi_engine::game::resources() noexcept -> resource_system&
{
    return this->m_resources;
}

auto noi_engine::game::input() -> input_state&
{
    return this->m_input;
}

auto noi_engine::game::run(const int argc, char** argv) -> int
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
