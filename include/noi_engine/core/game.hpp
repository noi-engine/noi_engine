//
// Created by ricka on 2026-07-30.
//

#pragma once
#include <memory>

#include <noi_engine/core/window.hpp>

namespace noi_engine
{
	struct game_conf
	{
	};

	class game
	{
		std::unique_ptr<window> window{ nullptr };

	public:
		explicit game(const std::string& title, int width, int height,
		              const game_conf& conf = game_conf());

		virtual ~game();

		virtual auto run(int argc, char** argv) -> int;
	};
}