//
// Created by ricka on 8/1/26.
//

#pragma once

#include <array>
#include <SDL2/SDL_events.h>
#include <glm/vec2.hpp>

namespace noi_engine
{
    class input_state
    {
        std::array<bool, SDL_NUM_SCANCODES> m_keys_down{};
        std::array<bool, SDL_NUM_SCANCODES> m_keys_pressed{};
        std::array<bool, SDL_NUM_SCANCODES> m_keys_released{};

        std::array<bool, 5> m_mouse_buttons_down{};
        std::array<bool, 5> m_mouse_buttons_pressed{};
        std::array<bool, 5> m_mouse_buttons_released{};

        glm::vec2 m_mouse_position{0.0f};
        glm::vec2 m_mouse_delta{0.0f};
        float m_scroll_delta{0.0f};

    public:
        auto begin_frame() -> void;

        auto process_event(const SDL_Event& event) -> void;

        [[nodiscard]] auto is_key_down(SDL_Scancode key) const -> bool;
        [[nodiscard]] auto is_key_pressed(SDL_Scancode key) const -> bool;
        [[nodiscard]] auto is_key_released(SDL_Scancode key) const -> bool;

        [[nodiscard]] auto is_mouse_button_down(uint8_t button) const -> bool;
        [[nodiscard]] auto is_mouse_button_pressed(uint8_t button) const -> bool;
        [[nodiscard]] auto is_mouse_button_released(uint8_t button) const -> bool;

        [[nodiscard]] auto get_mouse_position() const -> glm::vec2;
        [[nodiscard]] auto get_mouse_delta() const -> glm::vec2;
        [[nodiscard]] auto get_scroll_delta() const -> float;
    };
}
