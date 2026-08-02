//
// Created by ricka on 8/2/26.
//

#include <gtest/gtest.h>

#include <noi_engine/core/ecs/world.hpp>
#include <core/systems/transform_system.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/world_matrix.hpp>
#include <noi_engine/core/components/dirty.hpp>

using namespace noi_engine;

TEST(TransformSystemTest, SyncUpdatesWorldMatrixAndRemovesDirty)
{
    world w;

    const auto e = w.create_entity();

    w.add(e, transform{
              .position = {1.0f, 2.0f, 3.0f},
              .rotation = {0.0f, 0.0f, 0.0f},
              .scale = {1.0f, 1.0f, 1.0f}
          });

    w.add(e, world_matrix{});
    w.add(e, dirty<transform>{});

    transform_system::sync(w);

    EXPECT_TRUE(w.has<world_matrix>(e));
    EXPECT_FALSE(w.has<dirty<transform>>(e));

    const auto& matrix = w.get<world_matrix>(e).value;

    EXPECT_FLOAT_EQ(matrix[3][0], 1.0f);
    EXPECT_FLOAT_EQ(matrix[3][1], 2.0f);
    EXPECT_FLOAT_EQ(matrix[3][2], 3.0f);
}


TEST(TransformSystemTest, DoesNotSyncWithoutDirty)
{
    world w;

    const auto e = w.create_entity();

    w.add(e, transform{
              .position = {5.0f, 6.0f, 7.0f}
          });

    w.add(e, world_matrix{});

    transform_system::sync(w);

    EXPECT_FALSE(w.has<dirty<transform>>(e));

    const auto& matrix = w.get<world_matrix>(e).value;

    EXPECT_FLOAT_EQ(matrix[3][0], 0.0f);
    EXPECT_FLOAT_EQ(matrix[3][1], 0.0f);
    EXPECT_FLOAT_EQ(matrix[3][2], 0.0f);
}


TEST(TransformSystemTest, SyncOnlyDirtyEntities)
{
    world w;

    const auto dirty_entity = w.create_entity();
    const auto clean_entity = w.create_entity();

    w.add(dirty_entity, transform{
              .position = {10.0f, 0.0f, 0.0f}
          });
    w.add(dirty_entity, world_matrix{});
    w.add(dirty_entity, dirty<transform>{});

    w.add(clean_entity, transform{
              .position = {20.0f, 0.0f, 0.0f}
          });
    w.add(clean_entity, world_matrix{});

    transform_system::sync(w);

    EXPECT_FALSE(w.has<dirty<transform>>(dirty_entity));
    EXPECT_FALSE(w.has<dirty<transform>>(clean_entity));

    EXPECT_FLOAT_EQ(
        w.get<world_matrix>(dirty_entity).value[3][0],
        10.0f
    );

    EXPECT_FLOAT_EQ(
        w.get<world_matrix>(clean_entity).value[3][0],
        0.0f
    );
}
