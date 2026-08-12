//
// Created by ricka on 8/9/26.
//

#pragma once

#include <array>
#include <glm/vec2.hpp>
#include <noi_engine/core/input/input_codes.hpp>

namespace noi_engine
{
    class input_state_impl
    {
        static constexpr size_t KEY_COUNT = static_cast<size_t>(key_code::max_keys);
        static constexpr size_t MOUSE_BUTTON_COUNT = static_cast<size_t>(mouse_button::max_buttons);

        std::array<bool, KEY_COUNT> m_keys_down{};
        std::array<bool, KEY_COUNT> m_keys_pressed{};
        std::array<bool, KEY_COUNT> m_keys_released{};

        std::array<bool, MOUSE_BUTTON_COUNT> m_mouse_buttons_down{};
        std::array<bool, MOUSE_BUTTON_COUNT> m_mouse_buttons_pressed{};
        std::array<bool, MOUSE_BUTTON_COUNT> m_mouse_buttons_released{};

        glm::vec2 m_mouse_position{0.0f};
        glm::vec2 m_mouse_delta{0.0f};
        float m_scroll_delta{0.0f};

    public:
        auto begin_frame() -> void;

        auto set_key_pressed(key_code key) -> void;
        auto set_key_released(key_code key) -> void;

        auto set_mouse_button_pressed(mouse_button button) -> void;
        auto set_mouse_button_released(mouse_button button) -> void;
        auto set_mouse_position(glm::vec2 position) -> void;
        auto add_scroll_delta(float delta) -> void;

        [[nodiscard]] auto is_key_down(key_code key) const -> bool;
        [[nodiscard]] auto is_key_pressed(key_code key) const -> bool;
        [[nodiscard]] auto is_key_released(key_code key) const -> bool;

        [[nodiscard]] auto is_mouse_button_down(mouse_button button) const -> bool;
        [[nodiscard]] auto is_mouse_button_pressed(mouse_button button) const -> bool;
        [[nodiscard]] auto is_mouse_button_released(mouse_button button) const -> bool;

        [[nodiscard]] auto get_mouse_position() const -> glm::vec2;
        [[nodiscard]] auto get_mouse_delta() const -> glm::vec2;
        [[nodiscard]] auto get_scroll_delta() const -> float;
    };
}
