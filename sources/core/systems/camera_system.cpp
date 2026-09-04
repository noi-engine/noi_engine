//
// Created by ricka on 2026-09-04.
//

#include "camera_system.hpp"

#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/camera_3d.hpp>
#include <noi_engine/core/scene.hpp>

#include "camera_2d_system.hpp"
#include "camera_3d_system.hpp"

auto noi_engine::camera_system::on_update(const script_context& ctx, [[maybe_unused]] const float dt) -> void
{
	auto& world = ctx.get_world();
	const auto camera_entity = ctx.scene->get_camera_entity();

	if (world.has<camera_2d>(camera_entity))
	{
		camera_2d_system::update(world, camera_entity, *ctx.input);
	}
	else if (world.has<camera_3d>(camera_entity))
	{
		camera_3d_system::update(world, camera_entity, *ctx.input);
	}
}
