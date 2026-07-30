//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/ecs/component_pool.hpp>

auto noi_engine::world::create_entity() -> entity
{
	const auto e = m_entity_manager.create();
	m_entities.push_back(e);
	return e;
}

auto noi_engine::world::destroy_entity(const entity entity) -> void
{
	m_entity_manager.destroy(entity);
}