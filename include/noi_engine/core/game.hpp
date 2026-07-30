//
// Created by ricka on 2026-07-30.
//

#pragma once
#include <memory>

#include <noi_engine/core/window.hpp>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/scene_manager.hpp>

namespace noi_engine
{
	struct game_conf
	{
	};

	class game
	{
		bool m_running{ false };
		std::unique_ptr<window> m_window{ nullptr };
		std::unique_ptr<scene_manager> m_scene_manager{ nullptr };

	protected:
		virtual auto render() -> void;

		virtual auto process_events() -> void;

		virtual auto update(float dt) -> void;

	public:
		explicit game(const std::string& title, int width, int height,
		              const game_conf& conf = game_conf());

		virtual ~game();

		auto set_scene(std::unique_ptr<scene> scene) -> void;

		[[nodiscard]] auto get_window() -> window&;

		[[nodiscard]] auto get_window() const -> const window&;

		virtual auto run(int argc, char** argv) -> int;
	};
}