//
// Created by ricka on 2026-07-30.
//

#include <algorithm>
#include <cassert>
#include <noi_engine/core/ecs/entity_manager.hpp>

auto noi_engine::entity_manager::create() -> entity
{
	uint32_t id;

	if (!m_free.empty())
	{
		id = m_free.back();
		m_free.pop_back();
	}
	else
	{
		id = m_next++;
		m_generation.push_back(0);
	}

	const auto e = entity{ .m_id = id, .m_generation = m_generation[id] };
	m_entities.push_back(e);
	return e;
}

auto noi_engine::entity_manager::destroy(const entity e) -> void
{
	assert(valid(e));
	m_generation[e.m_id]++;
	m_free.push_back(e.m_id);

	const auto it = std::ranges::find(m_entities, e);

	if (it != m_entities.end())
	{
		*it = m_entities.back();
		m_entities.pop_back();
	}
}

auto noi_engine::entity_manager::valid(const entity e) const -> bool
{
	return e.m_id < m_generation.size() && m_generation[e.m_id] == e.
	       m_generation;
}

auto noi_engine::entity_manager::get_entities() const -> const std::vector<
	entity>&
{
	return this->m_entities;
}