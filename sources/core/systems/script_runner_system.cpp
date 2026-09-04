//
// Created by ricka on 2026-09-04.
//

#include "script_runner_system.hpp"

#include "script_system.hpp"

auto noi_engine::script_runner_system::on_before_update(const script_context& ctx, const float dt) -> void
{
	script_system::before_update(ctx, dt);
}

auto noi_engine::script_runner_system::on_update(const script_context& ctx, const float dt) -> void
{
	script_system::update(ctx, dt);
}

auto noi_engine::script_runner_system::on_after_update(const script_context& ctx, const float dt) -> void
{
	script_system::after_update(ctx, dt);
}

auto noi_engine::script_runner_system::on_before_render(const script_context& ctx) -> void
{
	script_system::before_render(ctx);
}

auto noi_engine::script_runner_system::on_after_render(const script_context& ctx) -> void
{
	script_system::after_render(ctx);
}
