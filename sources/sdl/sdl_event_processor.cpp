//
// Created by ricka on 8/9/26.
//

#include "sdl_event_processor.hpp"

namespace
{
    auto sdl_to_noi_key(SDL_Scancode scancode) -> noi_engine::key_code
    {
        if (static_cast<size_t>(scancode) < static_cast<size_t>(noi_engine::key_code::max_keys))
        {
            return static_cast<noi_engine::key_code>(scancode);
        }
        return noi_engine::key_code::unknown;
    }

    auto sdl_to_noi_mouse_button(uint8_t button) -> noi_engine::mouse_button
    {
        switch (button)
        {
        case SDL_BUTTON_LEFT: return noi_engine::mouse_button::left;
        case SDL_BUTTON_MIDDLE: return noi_engine::mouse_button::middle;
        case SDL_BUTTON_RIGHT: return noi_engine::mouse_button::right;
        case SDL_BUTTON_X1: return noi_engine::mouse_button::x1;
        case SDL_BUTTON_X2: return noi_engine::mouse_button::x2;
        default: return noi_engine::mouse_button::unknown;
        }
    }
}

auto noi_engine::sdl_event_processor::process(const SDL_Event& event, input_state& input_state) -> void
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        if (!event.key.repeat)
        {
            const auto key_code = sdl_to_noi_key(event.key.keysym.scancode);
            input_state.set_key_pressed(key_code);
        }
        break;

    case SDL_KEYUP:
        {
            const auto key_code = sdl_to_noi_key(event.key.keysym.scancode);
            input_state.set_key_released(key_code);
            break;
        }

    case SDL_MOUSEBUTTONDOWN:
        {
            const auto button = sdl_to_noi_mouse_button(event.button.button);
            input_state.set_mouse_button_pressed(button);
            break;
        }

    case SDL_MOUSEBUTTONUP:
        {
            const auto button = sdl_to_noi_mouse_button(event.button.button);
            input_state.set_mouse_button_released(button);
            break;
        }

    case SDL_MOUSEMOTION:
        {
            const auto pos = glm::vec2{
                static_cast<float>(event.motion.x),
                static_cast<float>(event.motion.y)
            };
            input_state.set_mouse_position(pos);
            break;
        }

    case SDL_MOUSEWHEEL:
        {
            auto delta = static_cast<float>(event.wheel.y);
            if (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED)
            {
                delta *= -1.0f;
            }
            input_state.add_scroll_delta(delta);
            break;
        }

    default:
        break;
    }
}
