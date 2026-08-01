#pragma once

#include <chrono>

namespace noi_engine
{
	using clock = std::chrono::high_resolution_clock;

	class frame_limiter
	{
		clock::time_point m_start;
		double m_frame_time;

	public:
		explicit frame_limiter(int max_fps);

		auto begin() -> void;

		auto end() const -> void;
	};
}