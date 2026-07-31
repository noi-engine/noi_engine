//
// Created by ricka on 2026-07-31.
//
#include <gtest/gtest.h>

#include <chrono>
#include <iostream>

#include <noi_engine/core/ecs/component_pool.hpp>

using namespace noi_engine;

TEST(ComponentPoolTest, AddHasGetRemove)
{
	component_pool<int> pool;

	constexpr entity e1{ .m_id = 1 };
	constexpr entity e2{ .m_id = 2 };

	EXPECT_FALSE(pool.has(e1));
	EXPECT_FALSE(pool.has(e2));

	pool.add(e1, 42);
	pool.add(e2, 1337);

	EXPECT_TRUE(pool.has(e1));
	EXPECT_TRUE(pool.has(e2));

	EXPECT_EQ(pool.get(e1), 42);
	EXPECT_EQ(pool.get(e2), 1337);

	pool.remove(e1);

	EXPECT_FALSE(pool.has(e1));
	EXPECT_TRUE(pool.has(e2));

	EXPECT_EQ(pool.get(e2), 1337);
}

TEST(ComponentPoolTest, RemoveSwapsLastElement)
{
	component_pool<int> pool;

	constexpr entity e1{ .m_id = 1 };
	constexpr entity e2{ .m_id = 2 };
	constexpr entity e3{ .m_id = 3 };

	pool.add(e1, 10);
	pool.add(e2, 20);
	pool.add(e3, 30);

	pool.remove(e2);

	EXPECT_FALSE(pool.has(e2));

	EXPECT_TRUE(pool.has(e1));
	EXPECT_TRUE(pool.has(e3));

	EXPECT_EQ(pool.get(e1), 10);
	EXPECT_EQ(pool.get(e3), 30);
}

TEST(ComponentPoolTest, RemoveLastElement)
{
	component_pool<int> pool;

	constexpr entity e1{ .m_id = 1 };
	constexpr entity e2{ .m_id = 2 };

	pool.add(e1, 10);
	pool.add(e2, 20);

	pool.remove(e2);

	EXPECT_TRUE(pool.has(e1));
	EXPECT_FALSE(pool.has(e2));

	EXPECT_EQ(pool.get(e1), 10);
}

TEST(ComponentPoolTest, DenseArrayIsContiguous)
{
	component_pool<int> pool;

	for (uint32_t i = 0; i < 100; ++i)
	{
		pool.add({ .m_id = i }, static_cast<int>(i));
	}

	const auto& dense = pool.get_dense();

	EXPECT_EQ(dense.size(), 100);

	for (size_t i = 0; i < dense.size(); ++i)
	{
		EXPECT_EQ(dense[i], static_cast<int>(i));
	}
}

TEST(ComponentPoolPerformance, AddOneMillionComponents)
{
	using namespace std::chrono;

	component_pool<int> pool;

	constexpr uint32_t count = 1'000'000;

	const auto start = high_resolution_clock::now();

	for (uint32_t i = 0; i < count; ++i)
	{
		pool.add({ .m_id = i }, static_cast<int>(i));
	}

	const auto end = high_resolution_clock::now();

	const auto elapsed = duration_cast<milliseconds>(end - start);

	std::cout
		<< "\nAdd " << count
		<< " components : "
		<< elapsed.count()
		<< " ms\n";

	EXPECT_EQ(pool.get_entities().size(), count);
}

TEST(ComponentPoolPerformance, IterateOneMillionComponents)
{
	using namespace std::chrono;

	component_pool<int> pool;

	constexpr uint32_t count = 1'000'000;

	for (uint32_t i = 0; i < count; ++i)
	{
		pool.add({ .m_id = i }, static_cast<int>(i));
	}

	volatile long long sum = 0;

	const auto start = high_resolution_clock::now();

	for (const auto& value : pool.get_dense())
	{
		sum += value;
	}

	const auto end = high_resolution_clock::now();

	const auto elapsed = duration_cast<milliseconds>(end - start);

	std::cout
		<< "\nIterate " << count
		<< " components : "
		<< elapsed.count()
		<< " ms\n";

	EXPECT_GT(sum, 0);
}