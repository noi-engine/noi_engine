//
// Created by ricka on 2026-07-30.
//

#include <SDL2/SDL.h>
#include <gtest/gtest.h>
#include <noi_engine/core/sdl/sdl_window.hpp>

class WindowTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		SDL_Init(SDL_INIT_VIDEO);
	}

	void TearDown() override
	{
		SDL_Quit();
	}
};


TEST_F(WindowTest, CreateWindowWithCorrectSize)
{
	GTEST_SKIP();

	const noi_engine::sdl_window window("Test Window", 800, 600);

	const auto value = window.get_size();

	EXPECT_EQ(value.x, 800);
	EXPECT_EQ(value.y, 600);
}