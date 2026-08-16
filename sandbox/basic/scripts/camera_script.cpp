//
// Created by ricka on 8/9/26.
//

// #include <noi_engine/builtin/signals/moved_signal.hpp>
// #include <noi_engine/builtin/actions/basic.hpp>

#include "scripts.hpp"

auto sandbox::basic::camera_script::on_create(
	const noi_engine::entity self, const noi_engine::script_context& context)
	-> void
{
	/*connect<noi_engine::moved_signal>(
		context, m_player,
		[*this, context, self](const float dt,
							   const noi_engine::moved_signal& signal) -> void
		{
			noi_engine::actions::follow(dt, context,
										{ .target = signal.source,
										  .follower = self,
										  .offset = { 0.3, 0.3, 0.0 },
										  .smoothing = 0.3f });
		});
		*/
}
