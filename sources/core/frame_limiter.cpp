//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/frame_limiter.hpp>
#include <thread>

noi_engine::frame_limiter::frame_limiter(const int max_fps) : m_frame_time(
	1.0 / max_fps)
{
}

auto noi_engine::frame_limiter::begin() -> void
{
	this->m_start = clock::now();
}

auto noi_engine::frame_limiter::end() const -> void
{
	const auto elapsed = clock::now() - m_start;

	const double elapsed_seconds =
		std::chrono::duration<double>(elapsed).count();

	if (elapsed_seconds < m_frame_time)
	{
		const double remaining = m_frame_time - elapsed_seconds;
		std::this_thread::sleep_for(
			std::chrono::duration<double>(remaining));
	}
}