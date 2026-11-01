//
// Created by ricka on 2026-09-04.
//

#include "script_runner_system.hpp"

#include "script_system.hpp"

#include <noi_engine/core/scene.hpp>

namespace
{
	auto paused(const noi_engine::script_context& ctx) -> bool
	{
		return ctx.scene && ctx.scene->scripts_paused();
	}
}

auto noi_engine::script_runner_system::on_before_update(const script_context& ctx, const float dt) -> void
{
	if (paused(ctx)) return;
	script_system::before_update(ctx, dt);
}

auto noi_engine::script_runner_system::on_update(const script_context& ctx, const float dt) -> void
{
	if (paused(ctx)) return;
	script_system::update(ctx, dt);
}

auto noi_engine::script_runner_system::on_after_update(const script_context& ctx, const float dt) -> void
{
	if (paused(ctx)) return;
	script_system::after_update(ctx, dt);
}

auto noi_engine::script_runner_system::on_before_render(const script_context& ctx) -> void
{
	if (paused(ctx)) return;
	script_system::before_render(ctx);
}

auto noi_engine::script_runner_system::on_after_render(const script_context& ctx) -> void
{
	if (paused(ctx)) return;
	script_system::after_render(ctx);
}
