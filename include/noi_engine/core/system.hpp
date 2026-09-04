//
// Created by ricka on 2026-09-04.
//

#pragma once

#include <string_view>
#include <noi_engine/core/model/script.hpp>

namespace noi_engine
{
	class system
	{
	public:
		system() = default;
		system(const system&) = default;
		system(system&&) noexcept = default;
		auto operator=(const system&) -> system& = default;
		auto operator=(system&&) noexcept -> system& = default;
		virtual ~system() = default;

		virtual auto on_before_update([[maybe_unused]] const script_context& ctx,
									  [[maybe_unused]] float dt) -> void {}
		virtual auto on_update([[maybe_unused]] const script_context& ctx,
							   [[maybe_unused]] float dt) -> void {}
		virtual auto on_after_update([[maybe_unused]] const script_context& ctx,
									 [[maybe_unused]] float dt) -> void {}
		virtual auto on_before_render([[maybe_unused]] const script_context& ctx) -> void {}
		virtual auto on_render([[maybe_unused]] const script_context& ctx) -> void {}
		virtual auto on_after_render([[maybe_unused]] const script_context& ctx) -> void {}

		[[nodiscard]] virtual auto name() const -> std::string_view = 0;
	};
}  // namespace noi_engine
