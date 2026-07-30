//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <string>
#include <noi_engine/core/renderer/renderer.hpp>
#include <noi_engine/core/ecs/world.hpp>

namespace noi_engine
{
	class scene
	{
		std::string m_name{};
		world m_world{};

	public:
		explicit scene(std::string  name);

		virtual auto render(renderer& renderer) -> void;

		virtual auto update(float dt) -> void;

		[[nodiscard]] auto get_world() -> world&;

		virtual ~scene() = default;
	};
}