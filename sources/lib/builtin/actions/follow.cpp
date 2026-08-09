//
// Created by ricka on 8/9/26.
//

#include <algorithm>
#include <noi_engine/builtin/actions/basic.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/dirty.hpp>

auto noi_engine::actions::follow(const action_context& context, const follow_actions_params& params) -> void
{
    if (!context.world->has<transform>(params.target))
    {
        return;
    }

    if (!context.world->has<transform>(params.follower))
    {
        return;
    }

    auto& tr = context.world->get<transform>(params.follower);
    const auto desired = context.world->get<transform>(params.target).position + params.offset;


    if (params.smoothing <= 0.0f)
    {
        tr.position = desired;
    }
    else
    {
        const auto t = std::clamp(context.dt / params.smoothing, 0.0f, 1.0f);
        tr.position = tr.position + (desired - tr.position) * t;
    }

    context.world->add(params.follower, dirty<transform>{});
}
