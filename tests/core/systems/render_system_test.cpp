//
// Created by ricka on 8/2/26.
//

#include <gtest/gtest.h>

#include <core/systems/render_system.hpp>
#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/world_matrix.hpp>
#include <noi_engine/core/components/mesh_renderer.hpp>
#include <noi_engine/core/components/render_layer.hpp>

using namespace noi_engine;

namespace
{
    auto add_renderable(world& w, const int order) -> entity
    {
        const auto e = w.create_entity();
        w.add(e, transform{});
        w.add(e, world_matrix{});
        w.add(e, mesh_renderer{});

        if (order != 0)
            w.add(e, render_layer{.order = order});

        return e;
    }
}

TEST(RenderSystemTest, SortsEntitiesByLayerOrder)
{
    world w;

    const auto back = add_renderable(w, -1);
    const auto mid = add_renderable(w, 0);
    const auto front = add_renderable(w, 1);

    const auto renderables = render_system::sorted_renderables(w);

    ASSERT_EQ(renderables.size(), 3);
    EXPECT_EQ(renderables[0], back);
    EXPECT_EQ(renderables[1], mid);
    EXPECT_EQ(renderables[2], front);
}

TEST(RenderSystemTest, EntitiesWithoutRenderLayerDefaultToZero)
{
    world w;

    const auto no_layer = w.create_entity();
    w.add(no_layer, transform{});
    w.add(no_layer, world_matrix{});
    w.add(no_layer, mesh_renderer{});

    const auto behind = add_renderable(w, -5);

    const auto renderables = render_system::sorted_renderables(w);

    ASSERT_EQ(renderables.size(), 2);
    EXPECT_EQ(renderables[0], behind);
    EXPECT_EQ(renderables[1], no_layer);
}

TEST(RenderSystemTest, IgnoresEntitiesWithoutMeshRenderer)
{
    world w;

    const auto e = w.create_entity();
    w.add(e, transform{});

    const auto renderables = render_system::sorted_renderables(w);

    EXPECT_TRUE(renderables.empty());
}

TEST(RenderSystemTest, IgnoresEntitiesWithoutWorldMatrix)
{
    world w;

    const auto e = w.create_entity();
    w.add(e, transform{});
    w.add(e, mesh_renderer{});

    const auto renderables = render_system::sorted_renderables(w);

    EXPECT_TRUE(renderables.empty());
}