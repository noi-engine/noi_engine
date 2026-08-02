#include <gtest/gtest.h>

#include <noi_engine/core/ecs/world.hpp>

using namespace noi_engine;

namespace
{
    struct position_component
    {
        float x{};
        float y{};
        float z{};
    };

    struct tag_component
    {
    };
}


TEST(WorldTest, AddPositionAndTag)
{
    world w;

    const auto e = w.create_entity();

    w.add(e, position_component{.x = 1.0f, .y = 2.0f, .z = 3.0f});
    w.add(e, tag_component{});

    const auto& position = w.get<position_component>(e);

    EXPECT_FLOAT_EQ(position.x, 1.0f);
    EXPECT_FLOAT_EQ(position.y, 2.0f);
    EXPECT_FLOAT_EQ(position.z, 3.0f);

    EXPECT_TRUE(w.has<tag_component>(e));
}

TEST(WorldTest, ViewPositionTag)
{
    world w;

    const auto e1 = w.create_entity();
    const auto e2 = w.create_entity();

    w.add(e1, position_component{.x = 1, .y = 2, .z = 3});
    w.add(e1, tag_component{});

    w.add(e2, position_component{.x = 4, .y = 5, .z = 6});

    auto view = w.view<position_component, tag_component>();

    int count = 0;

    for (const auto e : view)
    {
        count++;

        const auto& value = w.get<position_component>(e);

        EXPECT_EQ(value.x, 1);
    }

    EXPECT_EQ(count, 1);
}
