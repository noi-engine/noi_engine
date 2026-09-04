//
// Created by ricka on 2026-09-04.
//

#pragma once

#include <noi_engine/core/system.hpp>

namespace noi_engine
{
	class script_runner_system : public system
	{
	public:
		auto on_before_update(const script_context& ctx, float dt) -> void override;
		auto on_update(const script_context& ctx, float dt) -> void override;
		auto on_after_update(const script_context& ctx, float dt) -> void override;
		auto on_before_render(const script_context& ctx) -> void override;
		auto on_after_render(const script_context& ctx) -> void override;

		[[nodiscard]] auto name() const -> std::string_view override { return "script_runner_system"; }
	};
}  // namespace noi_engine
