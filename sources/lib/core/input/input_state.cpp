//
// Created by ricka on 8/2/26.
//

#include <noi_engine/core/input/input_state.hpp>

auto noi_engine::input_state::begin_frame() -> void
{
	m_keys_pressed.fill(false);
	m_keys_released.fill(false);
	m_mouse_buttons_pressed.fill(false);
	m_mouse_buttons_released.fill(false);
	m_mouse_delta = glm::vec2{ 0.0f };
	m_scroll_delta = 0.0f;
}

auto noi_engine::input_state::process_event(const SDL_Event& event) -> void
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (!event.key.repeat)
		{
			m_keys_down[event.key.keysym.scancode] = true;
			m_keys_pressed[event.key.keysym.scancode] = true;
		}
		break;

	case SDL_KEYUP:
		m_keys_down[event.key.keysym.scancode] = false;
		m_keys_released[event.key.keysym.scancode] = true;
		break;

	case SDL_MOUSEBUTTONDOWN:
		m_mouse_buttons_down[event.button.button] = true;
		m_mouse_buttons_pressed[event.button.button] = true;
		break;

	case SDL_MOUSEBUTTONUP:
		m_mouse_buttons_down[event.button.button] = false;
		m_mouse_buttons_released[event.button.button] = true;
		break;

	case SDL_MOUSEMOTION:
		m_mouse_position = glm::vec2{
			static_cast<float>(event.motion.x),
			static_cast<float>(event.motion.y)
		};
		m_mouse_delta += glm::vec2{
			static_cast<float>(event.motion.xrel),
			static_cast<float>(event.motion.yrel)
		};
		break;

	case SDL_MOUSEWHEEL:
		m_scroll_delta += static_cast<float>(event.wheel.y);
		break;

	default:
		break;
	}
}

auto noi_engine::input_state::is_key_down(const SDL_Scancode key) const -> bool
{
	return m_keys_down[key];
}

auto noi_engine::input_state::is_key_pressed(const SDL_Scancode key) const -> bool
{
	return m_keys_pressed[key];
}

auto noi_engine::input_state::is_key_released(const SDL_Scancode key) const -> bool
{
	return m_keys_released[key];
}

auto noi_engine::input_state::is_mouse_button_down(const uint8_t button) const -> bool
{
	return m_mouse_buttons_down[button];
}

auto noi_engine::input_state::is_mouse_button_pressed(const uint8_t button) const -> bool
{
	return m_mouse_buttons_pressed[button];
}

auto noi_engine::input_state::is_mouse_button_released(const uint8_t button) const -> bool
{
	return m_mouse_buttons_released[button];
}

auto noi_engine::input_state::get_mouse_position() const -> glm::vec2
{
	return m_mouse_position;
}

auto noi_engine::input_state::get_mouse_delta() const -> glm::vec2
{
	return m_mouse_delta;
}

auto noi_engine::input_state::get_scroll_delta() const -> float
{
	return m_scroll_delta;
}