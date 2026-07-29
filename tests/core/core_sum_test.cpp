//
// Created by ricka on 2026-07-29.
//

#include <gtest/gtest.h>
#include <noi_engine/core/sum.hpp>

TEST(SumTest, AddsTwoNumbers)
{
	EXPECT_EQ(noi_engine::sum(2, 3), 5);
}

TEST(SumTest, HandlesNegativeNumbers)
{
	EXPECT_EQ(noi_engine::sum(-2, 3), 1);
}