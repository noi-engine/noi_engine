//
// Created by ricka on 8/1/26.
//

#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
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
        std::vector<std::string> m_labels{};
        std::unordered_map<std::string, uint32_t> m_label_to_id{};

    public:
        [[nodiscard]] auto create(std::unique_ptr<T> resource) -> resource_handle<T>;

        auto destroy(const resource_handle<T>& handle) -> void;

        [[nodiscard]] auto valid(const resource_handle<T>& handle) const -> bool;

        [[nodiscard]] auto get(const resource_handle<T>& handle) -> T*;

        [[nodiscard]] auto get(const resource_handle<T>& handle) const -> const T*;

        auto set_label(const resource_handle<T>& handle, std::string_view label) -> void;

        [[nodiscard]] auto get_label(const resource_handle<T>& handle) const -> std::string_view;

        [[nodiscard]] auto get_handle(std::string_view label) const -> resource_handle<T>;

        [[nodiscard]] auto entries() const -> std::vector<std::pair<std::string, resource_handle<T>>>;

        auto clear() -> void;
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
            m_labels.emplace_back();
        }

        m_labels[id].clear();

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

        m_label_to_id.erase(m_labels[handle.m_id]);
        m_labels[handle.m_id].clear();
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
        if (!valid(handle))
            return nullptr;

        return m_resources[handle.m_id].get();
    }

    template<typename T>
    auto resource_manager<T>::get(const resource_handle<T>& handle) const -> const T*
    {
        if (!valid(handle))
            return nullptr;

        return m_resources[handle.m_id].get();
    }

    template<typename T>
    auto resource_manager<T>::set_label(const resource_handle<T>& handle, const std::string_view label) -> void
    {
        if (!valid(handle))
            return;

        m_label_to_id.erase(m_labels[handle.m_id]);
        m_labels[handle.m_id] = label;
        m_label_to_id[m_labels[handle.m_id]] = handle.m_id;
    }

    template<typename T>
    auto resource_manager<T>::get_label(const resource_handle<T>& handle) const -> std::string_view
    {
        if (!valid(handle))
            return {};

        return m_labels[handle.m_id];
    }

    template<typename T>
    auto resource_manager<T>::get_handle(const std::string_view label) const -> resource_handle<T>
    {
        const auto it = m_label_to_id.find(std::string(label));
        if (it == m_label_to_id.end())
            return {};

        return resource_handle<T>{ .m_id = it->second, .m_generation = m_generations[it->second] };
    }

    template<typename T>
    auto resource_manager<T>::entries() const -> std::vector<std::pair<std::string, resource_handle<T>>>
    {
        std::vector<std::pair<std::string, resource_handle<T>>> result;
        for (uint32_t id = 0; id < static_cast<uint32_t>(m_resources.size()); ++id)
        {
            if (m_resources[id])
            {
                result.emplace_back(m_labels[id], resource_handle<T>{ .m_id = id, .m_generation = m_generations[id] });
            }
        }
        return result;
    }

    template<typename T>
    auto resource_manager<T>::clear() -> void
    {
        m_resources.clear();
        m_generations.clear();
        m_free.clear();
        m_labels.clear();
        m_label_to_id.clear();
    }
}
