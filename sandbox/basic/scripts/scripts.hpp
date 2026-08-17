//
// Created by ricka on 8/9/26.
//

#pragma once

#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/model/script.hpp>

namespace sandbox::basic
{
	class player_script : public noi_engine::script
	{
	public:
		auto on_update(noi_engine::entity self,
					   const noi_engine::script_context &context, float dt)
			-> void override;

		explicit player_script() = default;
	};

	class camera_script : public noi_engine::script
	{
	public:
		auto on_create(noi_engine::entity self,
					   const noi_engine::script_context &context)
			-> void override;

		explicit camera_script() = default;
	};
}  // namespace sandbox::basic
