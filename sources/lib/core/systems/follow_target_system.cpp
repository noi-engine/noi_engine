//
// Created by ricka on 8/2/26.
//

#include "follow_target_system.hpp"
#include <noi_engine/core/components/follow_target.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/dirty.hpp>
#include <algorithm>

auto noi_engine::follow_target_system::update(world& world, const float dt) -> void
{
    for (const auto e : world.view<follow_target, transform>())
    {
        const auto& follow = world.get<follow_target>(e);

        if (!world.has<transform>(follow.target))
            continue;

        const auto desired = world.get<transform>(follow.target).position + follow.offset;
        auto& tr = world.get<transform>(e);

        if (follow.smoothing <= 0.0f)
        {
            tr.position = desired;
        }
        else
        {
            const auto t = std::clamp(dt / follow.smoothing, 0.0f, 1.0f);
            tr.position = tr.position + (desired - tr.position) * t;
        }

        world.add(e, dirty<transform>{});
    }
}
