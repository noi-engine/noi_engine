//
// Created by ricka on 2026-09-04.
//

#include "fps_counter_system.hpp"

#include <cstdio>

auto sandbox::fps_counter_system::on_update(
    [[maybe_unused]] const noi_engine::script_context& ctx, const float dt) -> void
{
    m_elapsed += dt;
    ++m_frames;

    if (m_elapsed >= 1.0f)
    {
        std::printf("[fps_counter_system] %d fps\n", m_frames);
        m_elapsed = 0.0f;
        m_frames = 0;
    }
}
