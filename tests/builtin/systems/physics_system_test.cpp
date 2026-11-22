//
// Created by ricka on 9/25/26.
//

#include <gtest/gtest.h>
#include <chrono>
#include <vector>

#include <noi_engine/builtin/systems/physics_system.hpp>
#include <noi_engine/builtin/components/gravity.hpp>
#include <noi_engine/builtin/components/box_collider.hpp>
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

namespace
{
    auto add_box(world& w, const glm::vec3& position, const box_collider& box, const bool dynamic) -> entity
    {
        const auto e = w.create_entity();
        w.add_transform(e, transform{.position = position});
        if (dynamic)
            w.add(e, gravity{});
        w.add(e, box);
        return e;
    }
}

TEST(PhysicsSystemTest, BodyRestingOnTheFloorIsGrounded)
{
    world w;

    add_box(w, {0.0f, 0.0f, 0.0f}, box_collider{.half_extents = {5.0f, 0.5f}, .is_static = true}, false);
    const auto body = add_box(w, {0.0f, 0.6f, 0.0f}, box_collider{.half_extents = {0.5f, 0.5f}}, true);

    physics_system::step(w, 0.01f);

    EXPECT_TRUE(w.get<gravity>(body).grounded);
}

TEST(PhysicsSystemTest, FallingBodyIsNotGrounded)
{
    world w;

    const auto body = add_box(w, {0.0f, 10.0f, 0.0f}, box_collider{}, true);

    physics_system::step(w, 0.01f);

    EXPECT_FALSE(w.get<gravity>(body).grounded);
}

TEST(PhysicsSystemTest, TriggerReportsButDoesNotPush)
{
    world w;

    add_box(w, {0.0f, 0.0f, 0.0f}, box_collider{.half_extents = {2.0f, 2.0f}, .is_static = true, .is_trigger = true}, false);
    const auto body = add_box(w, {0.0f, 0.5f, 0.0f}, box_collider{.half_extents = {0.5f, 0.5f}}, true);

    std::vector<physics_system::contact> contacts;
    physics_system::step(w, 0.0f, nullptr, contacts);

    ASSERT_EQ(contacts.size(), 1u);
    EXPECT_TRUE(contacts[0].trigger);
    EXPECT_FLOAT_EQ(w.get<transform>(body).position.y, 0.5f);
}

TEST(PhysicsSystemTest, LayersThatDoNotInteractDoNotCollide)
{
    world w;

    add_box(w, {0.0f, 0.0f, 0.0f}, box_collider{.half_extents = {5.0f, 0.5f}, .is_static = true, .layer = 2u, .mask = 2u}, false);
    const auto body = add_box(w, {0.0f, 0.6f, 0.0f}, box_collider{.half_extents = {0.5f, 0.5f}, .layer = 1u, .mask = 1u}, true);

    physics_system::step(w, 0.0f);

    EXPECT_FLOAT_EQ(w.get<transform>(body).position.y, 0.6f);
}

TEST(PhysicsSystemTest, ColliderOffsetMovesTheBox)
{
    world w;

    add_box(w, {0.0f, 0.0f, 0.0f}, box_collider{.half_extents = {5.0f, 0.5f}, .is_static = true}, false);
    // The entity sits 3 units above the floor but its box is offset 2.5 down, so it overlaps.
    const auto body = add_box(w, {0.0f, 3.2f, 0.0f}, box_collider{.half_extents = {0.5f, 0.5f}, .offset = {0.0f, -2.5f}}, true);

    physics_system::step(w, 0.0f);

    EXPECT_GT(w.get<transform>(body).position.y, 3.2f);
}

TEST(PhysicsSystemTest, ManyColliderPairsAreAllResolved)
{
    world w;

    // A long row of static boxes with a body in the middle of each: the sweep must not skip any.
    std::vector<entity> bodies;
    for (int i = 0; i < 50; ++i)
    {
        const auto x = static_cast<float>(i) * 4.0f;
        add_box(w, {x, 0.0f, 0.0f}, box_collider{.half_extents = {1.0f, 0.5f}, .is_static = true}, false);
        bodies.push_back(add_box(w, {x, 0.6f, 0.0f}, box_collider{.half_extents = {0.5f, 0.5f}}, true));
    }

    physics_system::step(w, 0.0f);

    for (const auto body : bodies)
        EXPECT_NEAR(w.get<transform>(body).position.y, 1.0f, 1e-4f);
}

// A scene with thousands of colliders must stay cheap: the step is sorted along x and only
// tests neighbours, so its cost follows the number of overlapping pairs, not the square of the
// number of colliders. The bound is generous (debug builds, shared CI machines): a step that
// compared every pair (4 million tests) would be far over it.
TEST(PhysicsSystemTest, ThousandsOfCollidersStayCheap)
{
    world w;

    for (int i = 0; i < 2500; ++i)
    {
        const auto x = static_cast<float>(i % 100) * 3.0f;
        const auto y = static_cast<float>(i / 100) * 3.0f;
        add_box(w, {x, y, 0.0f}, box_collider{.half_extents = {0.5f, 0.5f}, .is_static = true}, false);
    }
    for (int i = 0; i < 1500; ++i)
    {
        const auto x = static_cast<float>(i % 100) * 3.0f;
        const auto y = static_cast<float>(i / 100) * 3.0f + 1.5f;
        add_box(w, {x, y, 0.0f}, box_collider{.half_extents = {0.4f, 0.4f}}, true);
    }

    physics_system::step(w, 0.016f); // first step settles the overlaps

    const auto start = std::chrono::steady_clock::now();
    constexpr int steps = 5;
    for (int i = 0; i < steps; ++i)
        physics_system::step(w, 0.016f);
    const auto elapsed_ms =
        std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() / steps;

    EXPECT_LT(elapsed_ms, 150.0) << "a physics step with 4000 colliders took " << elapsed_ms << " ms";
}
