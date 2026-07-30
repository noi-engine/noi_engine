//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <string>
#include <noi_engine/core/renderer/renderer.hpp>

namespace noi_engine
{
	class scene
	{
		std::string m_name{};

	public:
		explicit scene(const std::string& name);

		virtual auto render(renderer& renderer) -> void;

		virtual auto update(float dt) -> void;

		virtual ~scene() = default;
	};
}