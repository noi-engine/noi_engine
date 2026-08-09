//
// Created by ricka on 8/9/26.
//

#pragma once

#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/signals/signal_channel.hpp>

namespace noi_engine
{
    template <typename Signal>
    concept is_signal = requires(Signal signal)
    {
        { signal.source } -> std::convertible_to<entity>;
    };

    class signal_bus
    {
    public:
        template <typename Signal>
            requires is_signal<Signal>
        auto emit(Signal signal) -> void
        {
            channel<Signal>().emit(std::move(signal));
        }

        template <typename Signal>
            requires is_signal<Signal>
        auto connect(signal_channel<Signal>::listener callback)
            -> signal_channel<Signal>::listener_id
        {
            return channel<Signal>().connect(std::move(callback));
        }

        template <typename Signal>
            requires is_signal<Signal>
        auto connect(entity source, std::function<void(float dt, const Signal&)> callback)
            -> signal_channel<Signal>::listener_id
        {
            return channel<Signal>().connect(
                [source, callback = std::move(callback)](const float dt, const Signal& signal) -> void
                {
                    if (signal.source == source)
                    {
                        callback(dt, signal);
                    }
                });
        }

        template <typename Signal>
            requires is_signal<Signal>
        auto disconnect(signal_channel<Signal>::listener_id id) -> void
        {
            channel<Signal>().disconnect(id);
        }

        auto dispatch(float dt) -> void;

    private:
        template <typename Signal>
            requires is_signal<Signal>
        auto channel() -> signal_channel<Signal>&
        {
            const auto type = std::type_index(typeid(Signal));

            if (!m_channels.contains(type))
            {
                m_channels[type] = std::make_unique<signal_channel<Signal>>();
            }

            return *static_cast<signal_channel<Signal>*>(m_channels[type].get());
        }

        std::unordered_map<std::type_index, std::unique_ptr<signal_channel_base>> m_channels{};
    };
}
