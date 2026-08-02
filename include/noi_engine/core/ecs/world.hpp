//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <memory>
#include <typeindex>
#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/ecs/component_pool.hpp>
#include <noi_engine/core/ecs/entity_manager.hpp>
#include <noi_engine/core/ecs/view.hpp>

namespace noi_engine
{
    class world
    {
        entity_manager m_entity_manager{};
        std::unordered_map<std::type_index, std::unique_ptr<
                               component_pool_base>> m_pools;

    protected:
        template <typename T>
        auto pool() -> component_pool<T>&
        {
            const auto id = std::type_index(typeid(T));

            if (!m_pools.contains(id))
            {
                m_pools[id] = std::make_unique<component_pool<T>>();
            }

            return *static_cast<component_pool<T>*>(m_pools[id].get());
        }

    public:
        [[nodiscard]] auto create_entity() -> entity;

        auto destroy_entity(entity entity) -> void;

        template <typename T>
        auto add(entity e, const T& comp) -> void
        {
            pool<T>().add(e, std::move(comp));
        }

        template <typename T>
        [[nodiscard]] auto get(entity e) -> T&
        {
            return pool<T>().get(e);
        }


        template <typename... Components>
        auto view()
        {
            return noi_engine::view<Components...>(pool<Components>()...);
        }

        template <typename T>
        auto remove(entity e) -> void
        {
            pool<T>().remove(e);
        }

        template <typename T>
        [[nodiscard]] auto has(entity e) -> bool
        {
            return pool<T>().has(e);
        }

        [[nodiscard]] auto get_entities() const -> const std::vector<entity>&;

        world() = default;
    };
}
