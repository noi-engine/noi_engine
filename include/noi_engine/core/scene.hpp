//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/input/input_state.hpp>
#include <noi_engine/core/renderer/renderer.hpp>
#include <string>

namespace noi_engine
{
	class game;

	struct scene_context
	{
		game* game{ nullptr };
		renderer* renderer{ nullptr };
		input_state* input{ nullptr };
		resources* resources{ nullptr };
	};

	class scene
	{
	protected:
		world m_world{};
		std::string m_name{};
		entity m_camera_entity{};


	public:
		explicit scene(std::string name);

		virtual auto render(const scene_context& context) -> void;

		virtual auto on_enter(const scene_context& context) -> void;
		virtual auto on_exit(const scene_context& context) -> void;

		virtual auto update(const scene_context& context, float dt) -> void;

		virtual auto on_resize(const scene_context& context, int width,
							   int height) -> void;

		[[nodiscard]] auto get_aspect_ratio() -> float;

		[[nodiscard]] auto get_world() -> world&;

		[[nodiscard]] auto get_camera_entity() const -> entity;

		virtual ~scene() = default;
	};
}  // namespace noi_engine
