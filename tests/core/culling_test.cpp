#include <gtest/gtest.h>

#include <noi_engine/builtin/components/gravity.hpp>
#include <noi_engine/builtin/systems/physics_system.hpp>
#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/culling.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/ecs/world.hpp>

using namespace noi_engine;

namespace
{
    auto add_camera(world& w, const glm::vec3& position) -> entity
    {
        const auto camera = w.create_entity();
        w.add_transform(camera, transform{.position = position});
        // 16 x 9 world units.
        w.add(camera, camera_2d{.aspect_ratio = 16.0f / 9.0f, .orthographic_size = 4.5f});
        return camera;
    }
}

TEST(CullingTest, NoAreaWithoutCullingComponent)
{
    world w;
    const auto camera = add_camera(w, {0.0f, 0.0f, 0.0f});
    view_area area;
    EXPECT_FALSE(culling_area(w, camera, area));
}

TEST(CullingTest, NoAreaWhenDisabled)
{
    world w;
    const auto camera = add_camera(w, {0.0f, 0.0f, 0.0f});
    w.add(camera, culling{.enabled = false});
    view_area area;
    EXPECT_FALSE(culling_area(w, camera, area));
}

TEST(CullingTest, AreaIsTheCameraViewPlusMargin)
{
    world w;
    const auto camera = add_camera(w, {10.0f, -2.0f, 0.0f});
    w.add(camera, culling{.margin = 1.0f});

    view_area area;
    ASSERT_TRUE(culling_area(w, camera, area));
    EXPECT_FLOAT_EQ(area.min.x, 10.0f - 8.0f - 1.0f);
    EXPECT_FLOAT_EQ(area.max.x, 10.0f + 8.0f + 1.0f);
    EXPECT_FLOAT_EQ(area.min.y, -2.0f - 4.5f - 1.0f);
    EXPECT_FLOAT_EQ(area.max.y, -2.0f + 4.5f + 1.0f);

    EXPECT_TRUE(area.overlaps({10.0f, -2.0f}, {0.5f, 0.5f}));
    EXPECT_TRUE(area.overlaps({19.4f, 0.0f}, {0.5f, 0.5f})); // touches the margin
    EXPECT_FALSE(area.overlaps({30.0f, 0.0f}, {0.5f, 0.5f}));
}

TEST(CullingTest, PhysicsLeavesBodiesOutsideTheAreaAlone)
{
    world w;
    const view_area area{.min = {-5.0f, -5.0f}, .max = {5.0f, 5.0f}};

    const auto inside = w.create_entity();
    w.add_transform(inside, transform{.position = {0.0f, 0.0f, 0.0f}});
    w.add(inside, gravity{});

    const auto outside = w.create_entity();
    w.add_transform(outside, transform{.position = {50.0f, 0.0f, 0.0f}});
    w.add(outside, gravity{});

    const auto always = w.create_entity();
    w.add_transform(always, transform{.position = {-50.0f, 0.0f, 0.0f}});
    w.add(always, gravity{});
    w.add(always, always_active{});

    physics_system::step(w, 0.1f, area);

    EXPECT_LT(w.get<transform>(inside).position.y, 0.0f);
    EXPECT_FLOAT_EQ(w.get<transform>(outside).position.y, 0.0f);
    EXPECT_LT(w.get<transform>(always).position.y, 0.0f);
}
