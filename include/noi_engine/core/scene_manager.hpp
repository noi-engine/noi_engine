//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <memory>
#include <noi_engine/core/input/input_state.hpp>
#include <noi_engine/core/renderer/renderer.hpp>
#include <noi_engine/core/scene.hpp>

namespace noi_engine
{
	class scene_manager
	{
		scene_context m_context;
		std::unique_ptr<scene> m_current{ nullptr };

	public:
		explicit scene_manager(const scene_context& context);

		virtual ~scene_manager() = default;

		auto set_scene(std::unique_ptr<scene> scene) -> void;

		auto update(float dt) const -> void;

		auto render() const -> void;

		[[nodiscard]] auto current() const -> scene*;

		auto on_resize(int width, int height) const -> void;
	};
}  // namespace noi_engine
