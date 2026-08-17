//
// Created by ricka on 8/9/26.
//

#include <noi_engine/builtin/actions/basic.hpp>

#include "scripts.hpp"
#include "../signals/moved_signal.hpp"

auto sandbox::basic::camera_script::on_create(
    const noi_engine::entity self, const noi_engine::script_context& context)
    -> void
{
    const auto player = context.get_world().find_by_name("player");
    connect<moved_signal>(
        context, player,
        [*this, context, self](const float dt, const moved_signal& signal) -> void
        {
            noi_engine::actions::follow(dt, context,
                                        {
                                            .target = signal.source,
                                            .follower = self,
                                            .offset = {0.3, 0.3, 0.0},
                                            .smoothing = 0.3f
                                        });
        });
}
