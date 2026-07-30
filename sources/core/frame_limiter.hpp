#pragma once

#include <chrono>
#include <thread>

namespace noi_engine
{
	class frame_limiter
	{
		using clock = std::chrono::high_resolution_clock;

		clock::time_point m_start;
		double m_frame_time;

	public:
		explicit frame_limiter(const int max_fps)
			: m_frame_time(1.0 / max_fps)
		{
		}

		auto begin() -> void
		{
			this->m_start = clock::now();
		}

		auto end() const -> void
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
	};
}