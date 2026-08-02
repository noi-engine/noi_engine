#include <gtest/gtest.h>

#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/camera_3d.hpp>

using namespace noi_engine;

TEST(WorldTest, AddTransformAndMesh)
{
	world w;

	const auto e = w.create_entity();

	w.add(e, transform{ .position = { 1.0f, 2.0f, 3.0f } });

	w.add(e, camera_3d{});

	const auto& [position, rotation, scale] = w.get<transform>(e);

	EXPECT_FLOAT_EQ(position.x, 1.0f);
	EXPECT_FLOAT_EQ(position.y, 2.0f);
	EXPECT_FLOAT_EQ(position.z, 3.0f);

	EXPECT_TRUE(w.pool<camera_3d>().has(e));
}


TEST(WorldTest, ViewTransformMesh)
{
	world w;

	const auto e1 = w.create_entity();
	const auto e2 = w.create_entity();

	w.add(e1, transform{ .position = { 1, 2, 3 } });
	w.add(e1, camera_3d{});

	w.add(e2, transform{ .position = { 4, 5, 6 } });

	auto view = w.view<transform, camera_3d>();

	int count = 0;

	for (const auto e : view)
	{
		count++;

		const auto& value = w.get<transform>(e);

		EXPECT_EQ(value.position.x, 1);
	}

	EXPECT_EQ(count, 1);
}