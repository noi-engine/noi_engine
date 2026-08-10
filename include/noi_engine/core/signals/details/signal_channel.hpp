//
// Created by ricka on 8/9/26.
//

#pragma once

#include <cstddef>
#include <functional>
#include <unordered_map>
#include <vector>

#ifdef emit
#  undef emit
#endif

namespace noi_engine::details
{
    class signal_channel_base
    {
    public:
        virtual ~signal_channel_base() = default;

        virtual auto dispatch(float dt) -> void = 0;
    };

    template <typename Signal>
    class signal_channel final : public signal_channel_base
    {
    public:
        using listener_id = std::size_t;
        using listener = std::function<void(float dt, const Signal&)>;

        auto emit(Signal signal) -> void
        {
            m_queue.push_back(std::move(signal));
        }

        [[nodiscard]] auto connect(listener callback) -> listener_id
        {
            const auto id = m_next_id++;
            m_listeners.emplace(id, std::move(callback));
            return id;
        }

        auto disconnect(const listener_id id) -> void
        {
            m_listeners.erase(id);
        }

        auto dispatch(float dt) -> void override
        {
            for (const auto& signal : m_queue)
            {
                for (const auto& [id, callback] : m_listeners)
                {
                    callback(dt, signal);
                }
            }

            m_queue.clear();
        }

    private:
        listener_id m_next_id{0};
        std::vector<Signal> m_queue{};
        std::unordered_map<listener_id, listener> m_listeners{};
    };
}
