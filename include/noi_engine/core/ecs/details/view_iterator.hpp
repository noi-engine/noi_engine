//
// Created by ricka on 2026-07-31.
//

#pragma once

#include <tuple>
#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/ecs/details/component_pool.hpp>

namespace noi_engine::details
{
    template <typename... Components>
    class view;

    template <typename... Components>
    class view_iterator
    {
        using first_component = std::tuple_element_t<
            0, std::tuple<Components...>>;
        using pool_type = component_pool<first_component>;

        pool_type* m_pool;
        size_t m_index;
        view<Components...>* m_view;

        auto skip_invalid() -> void
        {
            while (m_index < m_pool->get_entities().size())
            {
                if (m_view->valid(m_pool->get_entities()[m_index]))
                    break;

                ++m_index;
            }
        }

    public:
        view_iterator(pool_type& pool, size_t index, view<Components...>* view)
            : m_pool(&pool),
              m_index(index),
              m_view(view)
        {
            skip_invalid();
        }

        [[nodiscard]]
        auto operator*() const -> entity
        {
            return m_pool->get_entities()[m_index];
        }

        auto operator++() -> view_iterator&
        {
            ++m_index;
            skip_invalid();

            return *this;
        }

        [[nodiscard]]
        auto operator!=(const view_iterator& other) const -> bool
        {
            return m_index != other.m_index;
        }
    };
}
