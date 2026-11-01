//
// Created by ricka on 2026-09-04.
//

#include "bounds_system.hpp"

#include <algorithm>
#include <cstdio>

#include <noi_engine/core/components/dirty.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/ecs/world.hpp>

namespace
{
    constexpr float k_half_width = 8.0f;
    constexpr float k_half_height = 4.5f;
}  // namespace

auto sandbox::bounds_system::on_update(
    const noi_engine::script_context& ctx, [[maybe_unused]] const float dt) -> void
{
    auto& world = ctx.get_world();
    const auto player = world.find_by_name("player");

    if (!world.has<noi_engine::transform>(player))
        return;

    auto& tr = world.get<noi_engine::transform>(player);
    const auto clamped_x = std::clamp(tr.position.x, -k_half_width, k_half_width);
    const auto clamped_y = std::clamp(tr.position.y, -k_half_height, k_half_height);

    if (clamped_x == tr.position.x && clamped_y == tr.position.y)
        return;

    std::printf("[bounds_system] player hit the edge, clamping (%.2f, %.2f) -> (%.2f, %.2f)\n",
                tr.position.x, tr.position.y, clamped_x, clamped_y);

    tr.position.x = clamped_x;
    tr.position.y = clamped_y;

    if (!world.has<noi_engine::dirty<noi_engine::transform>>(player))
        world.add<noi_engine::dirty<noi_engine::transform>>(player, {});
}
