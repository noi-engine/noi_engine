//
// Created by ricka on 8/9/26.
//

#include "scripts.hpp"
#include <noi_engine/builtin/signals/moved_signal.hpp>
#include <noi_engine/builtin/actions/basic.hpp>

sandbox::basic::camera_script::camera_script(const noi_engine::entity player) : m_player(player)
{
}

auto sandbox::basic::camera_script::on_create() -> void
{
    connect<noi_engine::moved_signal>(
        m_player,
        [*this](const float dt, const noi_engine::moved_signal& signal) -> void
        {
            noi_engine::actions::follow({
                                            .dt = dt,
                                            .world = get_world(),
                                        },
                                        {
                                            .target = signal.source,
                                            .follower = get_self(),
                                            .offset = {0.3, 0.3, 0.0},
                                            .smoothing = 0.3f
                                        });
        });
}
