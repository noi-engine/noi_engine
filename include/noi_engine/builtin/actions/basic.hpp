//
// Created by ricka on 8/9/26.
//

#pragma once

#include <glm/vec3.hpp>
#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/model/script.hpp>

#define NOI_ENGINE_ACTION_FOLLOW(...) \
    noi_engine::actions::follow(dt, context, __VA_ARGS__)

namespace noi_engine::actions
{
	struct follow_actions_params
	{
		entity target{};
		entity follower{};
		glm::vec3 offset{ 0.0f };
		float smoothing{ 0.0f };
	};

	auto follow(float dt, const script_context& context,
				const follow_actions_params& params) -> void;
}  // namespace noi_engine::actions
