//
// Created by ricka on 2026-07-30.
//
#include <gtest/gtest.h>

#include "../../include/noi_engine/core/frame_limiter.hpp"

#include <chrono>
#include <thread>


TEST(FrameLimiterTest, LimitsFrameRate)
{
	using clock = std::chrono::high_resolution_clock;

	constexpr int max_fps = 60;
	constexpr double expected_frame_time_ms = 1000.0 / max_fps;

	noi_engine::frame_limiter limiter(max_fps);

	const auto start = clock::now();

	limiter.begin();

	std::this_thread::sleep_for(std::chrono::milliseconds(1));

	limiter.end();

	const auto end = clock::now();

	const double elapsed_ms =
		std::chrono::duration<double, std::milli>(end - start).count();


	EXPECT_GE(
		elapsed_ms,
		expected_frame_time_ms - 2.0
	);
}