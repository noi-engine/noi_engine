//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <memory>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/renderer/renderer.hpp>

namespace noi_engine
{
	class scene_manager
	{
		std::unique_ptr<scene> m_current{ nullptr };

	public:
		scene_manager() = default;

		virtual ~scene_manager() = default;

		auto set_scene(std::unique_ptr<scene> scene) -> void;

		auto update(float dt) -> void;

		auto render(renderer &renderer) -> void;
	};
}