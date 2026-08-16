//
// Created by ricka on 8/1/26.
//

#pragma once

#include <vector>
#include <noi_engine/core/resources/resource_handle.hpp>

namespace noi_engine::details
{
    template<typename T>
    class resource_manager
    {
        std::vector<std::unique_ptr<T>> m_resources{};
        std::vector<uint32_t> m_generations{};
        std::vector<uint32_t> m_free{};

    public:
        [[nodiscard]] auto create(std::unique_ptr<T> resource) -> resource_handle<T>;

        auto destroy(const resource_handle<T>& handle) -> void;

        [[nodiscard]] auto valid(const resource_handle<T>& handle) const -> bool;

        [[nodiscard]] auto get(const resource_handle<T>& handle) -> T*;

        [[nodiscard]] auto get(const resource_handle<T>& handle) const -> const T*;
    };

    template<typename T>
    auto resource_manager<T>::create(std::unique_ptr<T> resource) -> resource_handle<T>
    {
        uint32_t id;

        if (!m_free.empty())
        {
            id = m_free.back();
            m_free.pop_back();
            m_resources[id] = std::move(resource);
        }
        else
        {
            id = static_cast<uint32_t>(m_resources.size());
            m_resources.push_back(std::move(resource));
            m_generations.push_back(0);
        }

        return resource_handle<T>{ .m_id = id, .m_generation = m_generations[id] };
    }

    template<typename T>
    auto resource_manager<T>::destroy(const resource_handle<T>& handle) -> void
    {
        if (!valid(handle))
            return;

        m_resources[handle.m_id].reset();
        ++m_generations[handle.m_id];
        m_free.push_back(handle.m_id);
    }

    template<typename T>
    auto resource_manager<T>::valid(const resource_handle<T>& handle) const -> bool
    {
        return handle.m_id < m_generations.size() &&
               m_generations[handle.m_id] == handle.m_generation;
    }

    template<typename T>
    auto resource_manager<T>::get(const resource_handle<T>& handle) -> T*
    {
        return m_resources[handle.m_id].get();
    }

    template<typename T>
    auto resource_manager<T>::get(const resource_handle<T>& handle) const -> const T*
    {
        return m_resources[handle.m_id].get();
    }
}