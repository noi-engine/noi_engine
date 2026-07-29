//
// Created by ricka on 2026-07-30.
//

#pragma once

namespace noi_engine
{
	class game
	{
	public:
		game() = default;

		virtual ~game() = default;

		virtual auto run(int argc, char** argv) -> int;
	};
}