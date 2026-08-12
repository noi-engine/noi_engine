//
// Created by ricka on 8/9/26.
//

#include "input_state_impl.hpp"

namespace noi_engine
{
    auto input_state_impl::begin_frame() -> void
    {
        m_keys_pressed.fill(false);
        m_keys_released.fill(false);

        m_mouse_buttons_pressed.fill(false);
        m_mouse_buttons_released.fill(false);

        m_mouse_delta = glm::vec2{0.0f};
        m_scroll_delta = 0.0f;
    }

    auto input_state_impl::set_key_pressed(key_code key) -> void
    {
        const auto idx = static_cast<size_t>(key);
        if (idx >= KEY_COUNT) return;

        m_keys_pressed[idx] = true;
        m_keys_down[idx] = true;
    }

    auto input_state_impl::set_key_released(key_code key) -> void
    {
        const auto idx = static_cast<size_t>(key);
        if (idx >= KEY_COUNT) return;

        m_keys_released[idx] = true;
        m_keys_down[idx] = false;
    }

    auto input_state_impl::set_mouse_button_pressed(mouse_button button) -> void
    {
        const auto idx = static_cast<size_t>(button);
        if (idx >= MOUSE_BUTTON_COUNT) return;

        m_mouse_buttons_pressed[idx] = true;
        m_mouse_buttons_down[idx] = true;
    }

    auto input_state_impl::set_mouse_button_released(mouse_button button) -> void
    {
        const auto idx = static_cast<size_t>(button);
        if (idx >= MOUSE_BUTTON_COUNT) return;

        m_mouse_buttons_released[idx] = true;
        m_mouse_buttons_down[idx] = false;
    }

    auto input_state_impl::set_mouse_position(glm::vec2 position) -> void
    {
        m_mouse_delta = position - m_mouse_position;
        m_mouse_position = position;
    }

    auto input_state_impl::add_scroll_delta(float delta) -> void
    {
        m_scroll_delta += delta;
    }


    auto input_state_impl::is_key_down(key_code key) const -> bool
    {
        return m_keys_down[static_cast<size_t>(key)];
    }

    auto input_state_impl::is_key_pressed(key_code key) const -> bool
    {
        return m_keys_pressed[static_cast<size_t>(key)];
    }

    auto input_state_impl::is_key_released(key_code key) const -> bool
    {
        return m_keys_released[static_cast<size_t>(key)];
    }

    auto input_state_impl::is_mouse_button_down(mouse_button button) const -> bool
    {
        return m_mouse_buttons_down[static_cast<size_t>(button)];
    }

    auto input_state_impl::is_mouse_button_pressed(mouse_button button) const -> bool
    {
        return m_mouse_buttons_pressed[static_cast<size_t>(button)];
    }

    auto input_state_impl::is_mouse_button_released(mouse_button button) const -> bool
    {
        return m_mouse_buttons_released[static_cast<size_t>(button)];
    }

    auto input_state_impl::get_mouse_position() const -> glm::vec2 { return m_mouse_position; }
    auto input_state_impl::get_mouse_delta() const -> glm::vec2 { return m_mouse_delta; }
    auto input_state_impl::get_scroll_delta() const -> float { return m_scroll_delta; }
}
