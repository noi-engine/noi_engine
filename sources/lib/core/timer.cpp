//
// Created by ricka on 2026-07-30.
//

#include "timer.hpp"

noi_engine::timer::timer() : m_last(std::chrono::steady_clock::now())
{
}

auto noi_engine::timer::tick() -> float
{
    const auto now = std::chrono::steady_clock::now();
    const float dt = std::chrono::duration<float>(now - m_last).count();

    m_last = now;
    return dt;
}
