//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <vector>
#include <unordered_map>
#include <noi_engine/core/ecs/entity.hpp>

namespace noi_engine
{
	template<typename T>
	class component_pool
	{
		std::vector<T> m_dense{};
		std::vector<entity> m_entities{};
		std::unordered_map<uint32_t, size_t> m_sparse{};

	public:
		auto add(const entity e, T value) -> void
		{
			if (has(e))
				return;

			m_sparse[e.m_id] = m_dense.size();
			m_dense.push_back(value);
			m_entities.push_back(e);
		}

		auto remove(const entity e) -> void
		{
			if (!has(e))
				return;

			size_t index = m_sparse[e.m_id];
			size_t last = m_dense.size() - 1;

			m_dense[index] = m_dense[last];
			m_entities[index] = m_entities[last];
			m_sparse[m_entities[index].m_id] = index;

			m_dense.pop_back();
			m_entities.pop_back();
			m_sparse.erase(e.m_id);
		}

		[[nodiscard]] auto has(const entity e) const -> bool
		{
			return m_sparse.contains(e.m_id);
		}

		[[nodiscard]] auto get(const entity e) -> T&
		{
			return m_dense[m_sparse[e.m_id]];
		}

		[[nodiscard]] auto get_entities() -> std::vector<entity>&
		{
			return m_entities;
		}

		[[nodiscard]] auto get_dense() -> std::vector<T>&
		{
			return m_dense;
		}
	};
}