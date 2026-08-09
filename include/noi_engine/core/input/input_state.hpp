//
// Created by ricka on 8/1/26.
//

#pragma once

#include <memory>
#include <glm/vec2.hpp>
#include <noi_engine/core/input/input_codes.hpp>

namespace noi_engine
{
    class input_state_impl;

    class input_state
    {
        std::unique_ptr<input_state_impl> m_impl{nullptr};

    public:
        explicit input_state();

        auto begin_frame() const -> void;

        auto set_key_pressed(key_code key) const -> void;
        auto set_key_released(key_code key) const -> void;

        auto set_mouse_button_pressed(mouse_button button) const -> void;
        auto set_mouse_button_released(mouse_button button) const -> void;
        auto set_mouse_position(glm::vec2 position) const -> void;
        auto add_scroll_delta(float delta) const -> void;

        [[nodiscard]] auto is_key_down(key_code key) const -> bool;
        [[nodiscard]] auto is_key_pressed(key_code key) const -> bool;
        [[nodiscard]] auto is_key_released(key_code key) const -> bool;

        [[nodiscard]] auto is_mouse_button_down(mouse_button button) const -> bool;
        [[nodiscard]] auto is_mouse_button_pressed(mouse_button button) const -> bool;
        [[nodiscard]] auto is_mouse_button_released(mouse_button button) const -> bool;

        [[nodiscard]] auto get_mouse_position() const -> glm::vec2;
        [[nodiscard]] auto get_mouse_delta() const -> glm::vec2;
        [[nodiscard]] auto get_scroll_delta() const -> float;

        ~input_state();
        input_state(input_state&&) noexcept;
        auto operator=(input_state&&) noexcept -> input_state&;

        input_state(const input_state&) = delete;
        auto operator=(const input_state&) -> input_state& = delete;
    };
}
