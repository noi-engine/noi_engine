//
// Created by ricka on 8/2/26.
//

#include <noi_engine/core/input/input_state.hpp>
#include "input_state_impl.hpp"

namespace noi_engine
{
    input_state::~input_state() = default;
    input_state::input_state(input_state&&) noexcept = default;
    auto input_state::operator=(input_state&&) noexcept -> input_state& = default;

    input_state::input_state()
    {
        this->m_impl = std::make_unique<input_state_impl>();
    }

    auto input_state::begin_frame() const -> void
    {
        this->m_impl->begin_frame();
    }

    auto input_state::set_key_pressed(const key_code key) const -> void
    {
        this->m_impl->set_key_pressed(key);
    }

    auto input_state::set_key_released(const key_code key) const -> void
    {
        this->m_impl->set_key_released(key);
    }

    auto input_state::set_mouse_button_pressed(const mouse_button button) const -> void
    {
        this->m_impl->set_mouse_button_pressed(button);
    }

    auto input_state::set_mouse_button_released(const mouse_button button) const -> void
    {
        this->m_impl->set_mouse_button_released(button);
    }

    auto input_state::set_mouse_position(const glm::vec2 position) const -> void
    {
        this->m_impl->set_mouse_position(position);
    }

    auto input_state::add_scroll_delta(const float delta) const -> void
    {
        this->m_impl->add_scroll_delta(delta);
    }

    auto input_state::is_key_down(const key_code key) const -> bool
    {
        return this->m_impl->is_key_down(key);
    }

    auto input_state::is_key_pressed(const key_code key) const -> bool
    {
        return this->m_impl->is_key_pressed(key);
    }

    auto input_state::is_key_released(const key_code key) const -> bool
    {
        return m_impl->is_key_released(key);
    }

    auto input_state::is_mouse_button_down(const mouse_button button) const -> bool
    {
        return m_impl->is_mouse_button_down(button);
    }

    auto input_state::is_mouse_button_pressed(const mouse_button button) const -> bool
    {
        return m_impl->is_mouse_button_pressed(button);
    }

    auto input_state::is_mouse_button_released(const mouse_button button) const -> bool
    {
        return m_impl->is_mouse_button_released(button);
    }

    auto input_state::get_mouse_position() const -> glm::vec2
    {
        return m_impl->get_mouse_position();
    }

    auto input_state::get_mouse_delta() const -> glm::vec2
    {
        return m_impl->get_mouse_delta();
    }

    auto input_state::get_scroll_delta() const -> float
    {
        return m_impl->get_scroll_delta();
    }
}
