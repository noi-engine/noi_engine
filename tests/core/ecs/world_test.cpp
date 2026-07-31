#include <gtest/gtest.h>

#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/mesh.hpp>

using namespace noi_engine;

TEST(WorldTest, AddTransformAndMesh)
{
	world w;

	const auto e = w.create_entity();

	w.add(e, transform{ .position = { 1.0f, 2.0f, 3.0f } });

	w.add(e, mesh{});

	const auto& [position, rotation, scale] = w.get<transform>(e);

	EXPECT_FLOAT_EQ(position.x, 1.0f);
	EXPECT_FLOAT_EQ(position.y, 2.0f);
	EXPECT_FLOAT_EQ(position.z, 3.0f);

	EXPECT_TRUE(w.pool<mesh>().has(e));
}


TEST(WorldTest, ViewTransformMesh)
{
	world w;

	const auto e1 = w.create_entity();
	const auto e2 = w.create_entity();

	w.add(e1, transform{ .position = { 1, 2, 3 } });
	w.add(e1, mesh{});

	w.add(e2, transform{ .position = { 4, 5, 6 } });

	auto view = w.view<transform, mesh>();

	int count = 0;

	for (const auto e : view)
	{
		count++;

		const auto& value = w.get<transform>(e);

		EXPECT_EQ(value.position.x, 1);
	}

	EXPECT_EQ(count, 1);
}