//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <cstdint>

namespace noi_engine
{
	struct entity
	{
		uint32_t m_id;
		uint32_t m_generation;

		auto operator==(const entity& other) const -> bool
		{
			return m_id == other.m_id &&
			       m_generation == other.m_generation;
		}
	};

	inline auto pack(const entity e) -> uint64_t
	{
		return (static_cast<uint64_t>(e.m_generation) << 32) | e.m_id;
	}

	inline auto unpack(const uint64_t v) -> entity
	{
		return entity{
			.m_id = static_cast<uint32_t>(v & 0xFFFFFFFF),
			.m_generation = static_cast<uint32_t>(v >> 32)
		};
	}
}