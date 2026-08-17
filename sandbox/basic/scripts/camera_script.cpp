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
    const auto player = NOI_ENGINE_FIND_ENTITY("player");

    auto callback = [*this, context, self](const float dt, const moved_signal& signal) -> void
    {
        NOI_ENGINE_ACTION_FOLLOW({
                                 .target = signal.source,
                                 .follower = self,
                                 .offset = {0.3f, 0.3f, 0.0f},
                                 .smoothing = 0.3f
                                 });
    };

    NOI_ENGINE_CONNECT(moved_signal, player, callback);
}
