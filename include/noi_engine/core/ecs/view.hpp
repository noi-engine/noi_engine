#pragma once

#include <tuple>
#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/ecs/component_pool.hpp>
#include <noi_engine/core/ecs/view_iterator.hpp>

namespace noi_engine
{
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