//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/ecs/world.hpp>

#include <ranges>
#include <noi_engine/core/ecs/component_pool.hpp>

auto noi_engine::world::create_entity() -> entity
{
    return m_entity_manager.create();
}

auto noi_engine::world::signals() -> signal_bus&
{
    return this->m_signals;
}

auto noi_engine::world::destroy_entity(const entity entity) -> void
{
    for (const auto& pool : m_pools | std::views::values)
    {
        pool->remove(entity);
    }

    m_entity_manager.destroy(entity);
}

auto noi_engine::world::get_entities() const -> const std::vector<entity>&
{
    return this->m_entity_manager.get_entities();
}
