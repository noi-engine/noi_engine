//
// Created by ricka on 9/25/26.
//

#include <gtest/gtest.h>

#include <noi_engine/builtin/physics/physics_system.hpp>
#include <noi_engine/builtin/physics/gravity.hpp>
#include <noi_engine/builtin/physics/box_collider.hpp>
#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/dirty.hpp>

using namespace noi_engine;

namespace
{
    auto add_falling_body(world& w, const glm::vec3& position) -> entity
    {
        const auto e = w.create_entity();
        w.add_transform(e, transform{.position = position});
        w.add(e, gravity{});
        return e;
    }
}

TEST(PhysicsSystemTest, IgnoresEntitiesWithoutGravity)
{
    world w;

    const auto e = w.create_entity();
    w.add_transform(e, transform{.position = {0.0f, 10.0f, 0.0f}});

    physics_system::step(w, 1.0f);

    EXPECT_FLOAT_EQ(w.get<transform>(e).position.y, 10.0f);
}

TEST(PhysicsSystemTest, IntegratesVelocityAndPositionUnderGravity)
{
    world w;

    const auto e = add_falling_body(w, {0.0f, 10.0f, 0.0f});

    physics_system::step(w, 1.0f);

    const auto& g = w.get<gravity>(e);
    EXPECT_FLOAT_EQ(g.velocity.y, -9.81f);
    EXPECT_FLOAT_EQ(w.get<transform>(e).position.y, 10.0f - 9.81f);
}

TEST(PhysicsSystemTest, DisabledGravityDoesNotMoveEntity)
{
    world w;

    const auto e = w.create_entity();
    w.add_transform(e, transform{.position = {0.0f, 10.0f, 0.0f}});
    w.add(e, gravity{.enabled = false});

    physics_system::step(w, 1.0f);

    EXPECT_FLOAT_EQ(w.get<transform>(e).position.y, 10.0f);
    EXPECT_FLOAT_EQ(w.get<gravity>(e).velocity.y, 0.0f);
}

TEST(PhysicsSystemTest, IntegrationMarksTransformDirty)
{
    world w;

    const auto e = add_falling_body(w, {0.0f, 10.0f, 0.0f});
    physics_system::step(w, 1.0f);

    EXPECT_TRUE(w.has<dirty<transform>>(e));
}

TEST(PhysicsSystemTest, DynamicColliderIsPushedOutOfStaticCollider)
{
    world w;

    const auto floor = w.create_entity();
    w.add_transform(floor, transform{.position = {0.0f, 0.0f, 0.0f}});
    w.add(floor, box_collider{.half_extents = {5.0f, 0.5f}, .is_static = true});

    // Already overlapping the floor by a hair; a small dt keeps gravity's nudge this frame
    // negligible so the resolved resting position stays predictable (half_extents.y + half_extents.y).
    const auto box = w.create_entity();
    w.add_transform(box, transform{.position = {0.0f, 0.6f, 0.0f}});
    w.add(box, gravity{});
    w.add(box, box_collider{.half_extents = {0.5f, 0.5f}});

    physics_system::step(w, 0.01f);

    EXPECT_NEAR(w.get<transform>(box).position.y, 1.0f, 1e-4f);
    EXPECT_FLOAT_EQ(w.get<gravity>(box).velocity.y, 0.0f);
}

TEST(PhysicsSystemTest, OverlappingDynamicCollidersSplitThePush)
{
    world w;

    const auto a = w.create_entity();
    w.add_transform(a, transform{.position = {0.0f, 0.0f, 0.0f}});
    w.add(a, gravity{});
    w.add(a, box_collider{.half_extents = {0.5f, 0.5f}});

    const auto b = w.create_entity();
    w.add_transform(b, transform{.position = {0.6f, 0.0f, 0.0f}});
    w.add(b, gravity{});
    w.add(b, box_collider{.half_extents = {0.5f, 0.5f}});

    physics_system::step(w, 0.0f);

    const auto separation = w.get<transform>(b).position.x - w.get<transform>(a).position.x;
    EXPECT_GT(separation, 0.6f);
}

TEST(PhysicsSystemTest, NonOverlappingCollidersAreUntouched)
{
    world w;

    const auto a = w.create_entity();
    w.add_transform(a, transform{.position = {0.0f, 0.0f, 0.0f}});
    w.add(a, gravity{});
    w.add(a, box_collider{.half_extents = {0.5f, 0.5f}});

    const auto b = w.create_entity();
    w.add_transform(b, transform{.position = {10.0f, 0.0f, 0.0f}});
    w.add(b, gravity{});
    w.add(b, box_collider{.half_extents = {0.5f, 0.5f}});

    physics_system::step(w, 0.0f);

    EXPECT_FLOAT_EQ(w.get<transform>(a).position.x, 0.0f);
    EXPECT_FLOAT_EQ(w.get<transform>(b).position.x, 10.0f);
}
