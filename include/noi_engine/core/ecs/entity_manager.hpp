//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <vector>
#include <noi_engine/core/ecs/entity.hpp>

namespace noi_engine
{
	class entity_manager
	{
		uint32_t m_next{0};
		std::vector<uint32_t> m_free{};
		std::vector<uint32_t> m_generation{};
		std::vector<entity> m_entities{};

	public:
		auto create() -> entity;

		auto destroy(entity e) -> void;

		[[nodiscard]] auto valid(entity e) const -> bool;
		[[nodiscard]] auto get_entities() const -> const std::vector<entity>&;
	};
}