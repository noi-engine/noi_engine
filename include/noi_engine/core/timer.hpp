//
// Created by ricka on 2026-07-30.
//

#pragma once
#include <chrono>

namespace noi_engine
{
	class timer
	{
		std::chrono::steady_clock::time_point m_last;

	public:
		timer();

		auto tick() -> float;
	};
}