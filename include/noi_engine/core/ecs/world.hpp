//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/ecs/component_pool.hpp>
#include <noi_engine/core/ecs/entity_manager.hpp>

namespace noi_engine
{
	class world
	{
		entity_manager m_entity_manager{};

	public:
		[[nodiscard]] auto create_entity() -> entity;
		auto destroy_entity(entity entity) -> void;

		template <typename T>
		auto add(entity e, T &comp) -> void
		{
			pool<T>().add(e, comp);
		}

		template<typename T>
		[[nodiscard]] auto get(entity e) -> T&
		{
			return pool<T>().get(e);
		}

		template<typename T>
		[[nodiscard]] auto pool() -> component_pool<T>&;

		world() = default;
	};
}