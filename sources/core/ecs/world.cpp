//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/components/name_component.hpp>
#include <noi_engine/core/ecs/world.hpp>
#include <ranges>

#include "entity_manager.hpp"

auto noi_engine::world::create_entity() const -> entity
{
	return m_entity_manager->create();
}

auto noi_engine::world::signals() -> details::signal_bus&
{
	return this->m_signals;
}

auto noi_engine::world::find_by_name(const std::string_view name) -> entity
{
	for (const auto entity : view<name_component>())
	{
		auto name_comp = get<name_component>(entity);
		if (name_comp.name == name)
		{
			return entity;
		}
	}
	return {};
}

auto noi_engine::world::destroy_entity(const entity entity) -> void
{
	for (const auto& pool : m_pools | std::views::values)
	{
		pool->remove(entity);
	}

	m_entity_manager->destroy(entity);
}

auto noi_engine::world::get_entities() const -> const std::vector<entity>&
{
	return this->m_entity_manager->get_entities();
}

noi_engine::world::world()
{
	this->m_entity_manager = std::make_unique<entity_manager>();
}

noi_engine::world::~world() = default;
