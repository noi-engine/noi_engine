//
// Created by ricka on 2026-07-31.
//

#include <gtest/gtest.h>

#include <vector>

#include <noi_engine/core/ecs/world.hpp>

using namespace noi_engine;

namespace
{
    struct position_component
    {
        int x{};
        int y{};
        int z{};
    };

    struct tag_component
    {
    };
}

TEST(ViewTest, EmptyView)
{
    world w;

    auto view = w.view<position_component>();

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

    w.add(e1, position_component{.x = 1, .y = 2, .z = 3});
    w.add(e2, position_component{.x = 4, .y = 5, .z = 6});

    auto view = w.view<position_component>();

    int count = 0;

    for (const auto e : view)
    {
        EXPECT_TRUE(w.has<position_component>(e));
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

    w.add(e1, position_component{.x = 1, .y = 2, .z = 3});
    w.add(e1, tag_component{});

    w.add(e2, position_component{.x = 4, .y = 5, .z = 6});

    w.add(e3, tag_component{});

    auto view = w.view<position_component, tag_component>();

    std::vector<entity> entities;

    for (auto e : view)
    {
        entities.push_back(e);
    }

    ASSERT_EQ(entities.size(), 1);
    EXPECT_EQ(entities[0], e1);
}

TEST(ViewTest, ViewReflectsNewComponents)
{
    world w;

    const auto e = w.create_entity();

    w.add(e, position_component{.x = 1, .y = 2, .z = 3});

    auto view = w.view<position_component, tag_component>();

    w.add(e, tag_component{});

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

    w.add(e, position_component{.x = 1, .y = 2, .z = 3});
    w.add(e, tag_component{});

    auto view = w.view<position_component, tag_component>();

    int before = 0;

    for ([[maybe_unused]] auto entity : view)
    {
        ++before;
    }

    EXPECT_EQ(before, 1);

    w.remove<tag_component>(e);

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

        w.add(e, position_component{.x = 0, .y = 0, .z = 0});

        if (i % 2 == 0)
        {
            w.add(e, tag_component{});
        }
    }

    auto view = w.view<position_component, tag_component>();

    int result = 0;

    for (const auto e : view)
    {
        EXPECT_TRUE(w.has<position_component>(e));
        EXPECT_TRUE(w.has<tag_component>(e));

        ++result;
    }

    EXPECT_EQ(result, count / 2);
}
