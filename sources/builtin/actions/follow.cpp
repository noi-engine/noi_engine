//
// Created by ricka on 8/9/26.
//

#include <algorithm>
#include <noi_engine/builtin/actions/basic.hpp>
#include <noi_engine/core/components/transform.hpp>

auto noi_engine::actions::follow(const float dt, const script_context& context,
								 const follow_actions_params& params) -> void
{
	auto& world = context.get_world();
	if (!world.has<transform>(params.target))
	{
		return;
	}

	if (!world.has<transform>(params.follower))
	{
		return;
	}

	auto& tr = world.get<transform>(params.follower);
	const auto desired =
		world.get<transform>(params.target).position + params.offset;

	if (params.smoothing <= 0.0f)
	{
		tr.position = desired;
	}
	else
	{
		const auto t = std::clamp(dt / params.smoothing, 0.0f, 1.0f);
		tr.position = tr.position + (desired - tr.position) * t;
	}

	world.add_dirty_transform(params.follower);
}
