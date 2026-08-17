//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <glm/vec2.hpp>
#include <SDL2/SDL_video.h>

#include <string>

namespace noi_engine
{
    struct sdl_window_conf
    {
    };

    class sdl_window
    {
    protected:
        SDL_Window* sdl_raw_window = nullptr;
        SDL_GLContext gl_context = nullptr;

    public:
        virtual ~sdl_window();

        explicit sdl_window(const std::string& title, int width, int height,
                            const sdl_window_conf& conf = {});

        [[nodiscard]] auto get_size() const -> glm::vec2;

        auto swap_buffers() const -> void;
    };
}
