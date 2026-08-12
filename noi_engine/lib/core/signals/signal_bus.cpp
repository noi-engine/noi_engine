//
// Created by ricka on 8/9/26.
//

#include <ranges>
#include <noi_engine/core/signals/details/signal_bus.hpp>

auto noi_engine::details::signal_bus::dispatch(const float dt) -> void
{
    for (const auto& channel : m_channels | std::views::values)
    {
        channel->dispatch(dt);
    }
}
