#include <gtest/gtest.h>

#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/fill_screen.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/world_matrix.hpp>
#include <noi_engine/core/ecs/world.hpp>

using namespace noi_engine;

TEST(FillScreenTest, CoversWhatTheCameraSees)
{
    world w;
    const auto camera = w.create_entity();
    w.add_transform(camera, transform{.position = {3.0f, -2.0f, 5.0f}});
    // 16 x 9 world units at zoom 1, 8 x 4.5 at zoom 2.
    w.add(camera, camera_2d{.zoom = 2.0f, .aspect_ratio = 16.0f / 9.0f, .orthographic_size = 4.5f});

    const auto background = w.create_entity();
    w.add_transform(background, transform{.position = {0.0f, 0.0f, -1.0f}});
    w.add(background, fill_screen{});

    apply_fill_screen(w, camera);

    const auto& tr = w.get<transform>(background);
    EXPECT_FLOAT_EQ(tr.position.x, 3.0f);
    EXPECT_FLOAT_EQ(tr.position.y, -2.0f);
    EXPECT_FLOAT_EQ(tr.position.z, -1.0f); // keeps its depth
    EXPECT_FLOAT_EQ(tr.scale.x, 8.0f);
    EXPECT_FLOAT_EQ(tr.scale.y, 4.5f);

    const auto& m = w.get<world_matrix>(background).value;
    EXPECT_FLOAT_EQ(m[3].x, 3.0f);
    EXPECT_FLOAT_EQ(m[0].x, 8.0f);
}

TEST(FillScreenTest, IgnoresEntitiesWithoutTheComponent)
{
    world w;
    const auto camera = w.create_entity();
    w.add_transform(camera, transform{.position = {3.0f, 3.0f, 0.0f}});
    w.add(camera, camera_2d{.aspect_ratio = 1.0f, .orthographic_size = 1.0f});

    const auto other = w.create_entity();
    w.add_transform(other, transform{});

    apply_fill_screen(w, camera);
    EXPECT_FLOAT_EQ(w.get<transform>(other).position.x, 0.0f);
    EXPECT_FLOAT_EQ(w.get<transform>(other).scale.x, 1.0f);
}
