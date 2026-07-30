//
// Created by ricka on 2026-07-30.
//

#include <gtest/gtest.h>

#include <noi_engine/core/ecs/entity.hpp>

//Generated
namespace noi_engine
{
	TEST(EntityTest, PackAndUnpackKeepsValues)
	{
		constexpr entity original{
			.m_id = 42,
			.m_generation = 7
		};

		const auto packed = pack(original);

		const auto [m_id, m_generation] = unpack(packed);

		EXPECT_EQ(m_id, original.m_id);
		EXPECT_EQ(m_generation, original.m_generation);
	}


	TEST(EntityTest, DifferentGenerationsProduceDifferentValues)
	{
		constexpr entity e1{
			.m_id = 10,
			.m_generation = 0
		};

		constexpr entity e2{
			.m_id = 10,
			.m_generation = 1
		};

		EXPECT_NE(pack(e1), pack(e2));
	}


	TEST(EntityTest, DifferentIdsProduceDifferentValues)
	{
		constexpr entity e1{
			.m_id = 10,
			.m_generation = 5
		};

		constexpr entity e2{
			.m_id = 11,
			.m_generation = 5
		};

		EXPECT_NE(pack(e1), pack(e2));
	}
}