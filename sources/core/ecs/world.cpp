//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/ecs/component_pool.hpp>

auto noi_engine::world::create_entity() -> entity
{
	return m_entity_manager.create();
}

auto noi_engine::world::destroy_entity(const entity entity) -> void
{
	m_entity_manager.destroy(entity);
}