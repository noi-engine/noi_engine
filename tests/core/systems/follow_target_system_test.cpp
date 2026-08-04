//
// Created by ricka on 8/2/26.
//

#include <gtest/gtest.h>

#include <lib/core/systems/follow_target_system.hpp>
#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/components/follow_target.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/dirty.hpp>

using namespace noi_engine;

TEST(FollowTargetSystemTest, SnapsToTargetWithoutSmoothing)
{
    world w;

    const auto target = w.create_entity();
    w.add(target, transform{.position = {5.0f, 2.0f, 0.0f}});

    const auto follower = w.create_entity();
    w.add(follower, transform{});
    w.add(follower, follow_target{.target = target, .offset = {0.0f, 1.0f, 0.0f}});

    follow_target_system::update(w, 0.016f);

    const auto& position = w.get<transform>(follower).position;

    EXPECT_FLOAT_EQ(position.x, 5.0f);
    EXPECT_FLOAT_EQ(position.y, 3.0f);
    EXPECT_TRUE(w.has<dirty<transform>>(follower));
}

TEST(FollowTargetSystemTest, SmoothsTowardTarget)
{
    world w;

    const auto target = w.create_entity();
    w.add(target, transform{.position = {10.0f, 0.0f, 0.0f}});

    const auto follower = w.create_entity();
    w.add(follower, transform{});
    w.add(follower, follow_target{.target = target, .smoothing = 1.0f});

    follow_target_system::update(w, 0.5f);

    const auto& position = w.get<transform>(follower).position;

    EXPECT_FLOAT_EQ(position.x, 5.0f);
}

TEST(FollowTargetSystemTest, IgnoresInvalidTarget)
{
    world w;

    const auto follower = w.create_entity();
    w.add(follower, transform{.position = {1.0f, 1.0f, 1.0f}});
    w.add(follower, follow_target{.target = entity{.m_id = 999, .m_generation = 0}});

    follow_target_system::update(w, 0.016f);

    const auto& position = w.get<transform>(follower).position;

    EXPECT_FLOAT_EQ(position.x, 1.0f);
    EXPECT_FLOAT_EQ(position.y, 1.0f);
}
