//
// Created by ricka on 8/2/26.
//

#pragma once

#include <noi_engine/core/scene.hpp>

namespace sandbox::basic
{
	class player_scene : public noi_engine::scene
	{
	public:
		player_scene();

		auto update(const noi_engine::scene_context& context, float dt)
			-> void override;

		auto on_enter(const noi_engine::scene_context& context)
			-> void override;
	};
}  // namespace sandbox::basic
