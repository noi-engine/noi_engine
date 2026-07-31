//
// Created by ricka on 2026-07-31.
//

#include <gtest/gtest.h>

#include <vector>

#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/mesh.hpp>

using namespace noi_engine;

TEST(ViewTest, EmptyView)
{
	world w;

	auto view = w.view<transform>();

	int count = 0;

	for ([[maybe_unused]] auto e : view)
		++count;

	EXPECT_EQ(count, 0);
}

TEST(ViewTest, SingleComponent)
{
	world w;

	const auto e1 = w.create_entity();
	const auto e2 = w.create_entity();

	w.add(e1, transform{ { 1.f, 2.f, 3.f } });
	w.add(e2, transform{ { 4.f, 5.f, 6.f } });

	auto view = w.view<transform>();

	int count = 0;

	for (const auto e : view)
	{
		EXPECT_TRUE(w.pool<transform>().has(e));
		++count;
	}

	EXPECT_EQ(count, 2);
}

TEST(ViewTest, MultipleComponents)
{
	world w;

	const auto e1 = w.create_entity();
	const auto e2 = w.create_entity();
	const auto e3 = w.create_entity();

	w.add(e1, transform{ { 1, 2, 3 } });
	w.add(e1, mesh{});

	w.add(e2, transform{ { 4, 5, 6 } });

	w.add(e3, mesh{});

	auto view = w.view<transform, mesh>();

	std::vector<entity> entities;

	for (auto e : view)
	{
		entities.push_back(e);
	}

	ASSERT_EQ(entities.size(), 1);
	EXPECT_EQ(entities[0].m_id, e1.m_id);
	EXPECT_EQ(entities[0].m_generation, e1.m_generation);
}

TEST(ViewTest, ViewReflectsNewComponents)
{
	world w;

	const auto e = w.create_entity();

	w.add(e, transform{ { 1, 2, 3 } });

	auto view = w.view<transform, mesh>();

	w.add(e, mesh{});

	int count = 0;

	for ([[maybe_unused]] auto entity : view)
	{
		++count;
	}

	EXPECT_EQ(count, 1);
}

TEST(ViewTest, RemoveComponentRemovesEntityFromView)
{
	world w;

	const auto e = w.create_entity();

	w.add(e, transform{ { 1, 2, 3 } });
	w.add(e, mesh{});

	auto view = w.view<transform, mesh>();

	int before = 0;

	for ([[maybe_unused]] auto entity : view)
	{
		++before;
	}

	EXPECT_EQ(before, 1);

	w.pool<mesh>().remove(e);

	int after = 0;

	for ([[maybe_unused]] auto entity : view)
	{
		++after;
	}

	EXPECT_EQ(after, 0);
}

TEST(ViewTest, IterationReturnsCorrectEntities)
{
	world w;

	constexpr int count = 100;

	for (int i = 0; i < count; ++i)
	{
		const auto e = w.create_entity();

		w.add(e, transform{ { 0, 0, 0 } });

		if (i % 2 == 0)
		{
			w.add(e, mesh{});
		}
	}

	auto view = w.view<transform, mesh>();

	int result = 0;

	for (const auto e : view)
	{
		EXPECT_TRUE(w.pool<transform>().has(e));
		EXPECT_TRUE(w.pool<mesh>().has(e));

		++result;
	}

	EXPECT_EQ(result, count / 2);
}