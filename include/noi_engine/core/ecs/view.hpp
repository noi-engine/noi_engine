#pragma once

#include <tuple>
#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/ecs/component_pool.hpp>

namespace noi_engine
{
	template<typename... Components>
	class view;

	template<typename... Components>
	class view_iterator
	{
		using first_component = std::tuple_element_t<
			0, std::tuple<Components...> >;
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


	template<typename... Components>
	class view
	{
		std::tuple<component_pool<Components>*...> m_pools;

		[[nodiscard]] auto valid(entity e) const -> bool
		{
			return (
				std::get<component_pool<Components>*>(m_pools)
				->has(e)
				&& ...
			);
		}

	public:
		explicit view(component_pool<Components>&... pools)
			: m_pools(&pools...)
		{
		}

		auto begin() -> view_iterator<Components...>
		{
			auto& first = *std::get<0>(m_pools);

			return view_iterator<Components...>(
				first,
				0,
				this
				);
		}

		auto end() -> view_iterator<Components...>
		{
			auto& first = *std::get<0>(m_pools);

			return view_iterator<Components...>(
				first,
				first.get_entities().size(),
				this);
		}

		friend class view_iterator<Components...>;
	};
}