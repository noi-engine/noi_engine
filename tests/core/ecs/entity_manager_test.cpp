//
// Created by ricka on 2026-07-30.
//

#include <gtest/gtest.h>

#include <noi_engine/core/ecs/entity_manager.hpp>

// Generated
namespace noi_engine
{
	TEST(EntityManagerTest, CreateEntityReturnsValidEntity)
	{
		entity_manager manager;

		const auto e = manager.create();

		EXPECT_TRUE(manager.valid(e));
	}


	TEST(EntityManagerTest, CreateEntitiesHaveDifferentIds)
	{
		entity_manager manager;

		const auto e1 = manager.create();
		const auto e2 = manager.create();

		EXPECT_NE(e1.m_id, e2.m_id);
		EXPECT_NE(pack(e1), pack(e2));
	}


	TEST(EntityManagerTest, DestroyEntityMakesItInvalid)
	{
		entity_manager manager;

		const auto e = manager.create();

		EXPECT_TRUE(manager.valid(e));

		manager.destroy(e);

		EXPECT_FALSE(manager.valid(e));
	}


	TEST(EntityManagerTest, DestroyAndReuseEntityIncrementsGeneration)
	{
		entity_manager manager;

		const auto old_entity = manager.create();

		const auto old_id = old_entity.m_id;
		const auto old_generation = old_entity.m_generation;

		manager.destroy(old_entity);

		const auto new_entity = manager.create();

		EXPECT_EQ(new_entity.m_id, old_id);
		EXPECT_EQ(new_entity.m_generation, old_generation + 1);

		EXPECT_FALSE(manager.valid(old_entity));
		EXPECT_TRUE(manager.valid(new_entity));
	}


	TEST(EntityManagerTest, MultipleDestroyedEntitiesCanBeReused)
	{
		entity_manager manager;

		const auto e1 = manager.create();
		const auto e2 = manager.create();
		const auto e3 = manager.create();

		manager.destroy(e1);
		manager.destroy(e2);
		manager.destroy(e3);

		const auto r1 = manager.create();
		const auto r2 = manager.create();
		const auto r3 = manager.create();

		EXPECT_TRUE(manager.valid(r1));
		EXPECT_TRUE(manager.valid(r2));
		EXPECT_TRUE(manager.valid(r3));

		EXPECT_EQ(r1.m_generation, 1);
		EXPECT_EQ(r2.m_generation, 1);
		EXPECT_EQ(r3.m_generation, 1);
	}


	TEST(EntityManagerTest, OldEntityCannotBecomeValidAgain)
	{
		entity_manager manager;

		const auto old = manager.create();

		manager.destroy(old);

		const auto new_entity = manager.create();

		EXPECT_EQ(old.m_id, new_entity.m_id);

		EXPECT_FALSE(manager.valid(old));
		EXPECT_TRUE(manager.valid(new_entity));
	}
}