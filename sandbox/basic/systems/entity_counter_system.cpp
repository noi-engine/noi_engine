//
// Created by ricka on 2026-09-04.
//

#include "entity_counter_system.hpp"

#include <cstdio>

#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/ecs/world.hpp>

auto sandbox::basic::entity_counter_system::on_update(
    const noi_engine::script_context& ctx, const float dt) -> void
{
    m_elapsed += dt;

    if (m_elapsed < 2.0f)
        return;

    m_elapsed = 0.0f;

    auto count = 0;
    for ([[maybe_unused]] const auto e : ctx.get_world().view<noi_engine::transform>())
        ++count;

    std::printf("[entity_counter_system] %d entities with a transform\n", count);
}
