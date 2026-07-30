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
		std::unique_ptr<window> m_window{ nullptr };

	public:
		explicit game(const std::string& title, int width, int height,
		              const game_conf& conf = game_conf());

		virtual ~game();

		[[nodiscard]] auto get_window() -> window&;

		[[nodiscard]] auto get_window() const -> const window&;

		virtual auto run(int argc, char** argv) -> int;
	};
}