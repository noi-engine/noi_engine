//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/camera_3d.hpp>
#include <noi_engine/core/components/dirty.hpp>
#include <noi_engine/core/components/world_matrix.hpp>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/model/script.hpp>
#include <utility>

#include "systems/camera_2d_system.hpp"
#include "systems/camera_3d_system.hpp"
#include "systems/render_system.hpp"
#include "systems/script_system.hpp"
#include "systems/transform_system.hpp"

static auto to_base_script_context(const noi_engine::scene_context& context,
								   noi_engine::scene* scene)
	-> noi_engine::script_context
{
	return { .game = context.game,
			 .scene = scene,
			 .input = context.input,
			 .renderer = context.renderer,
			 .resources = context.resources };
}

noi_engine::scene::scene(std::string name) : m_name(std::move(name))
{
	this->m_camera_entity = m_world.create_entity();
	m_world.add(m_camera_entity, transform{});
	m_world.add(m_camera_entity, world_matrix{});
	m_world.add(m_camera_entity, dirty<transform>{});
}

auto noi_engine::scene::update(const scene_context& context, const float dt)
	-> void
{
	const auto script_context = to_base_script_context(context, this);

	script_system::before_update(script_context, dt);

	script_system::update(script_context, dt);

	transform_system::sync(m_world);
	if (m_world.has<camera_2d>(m_camera_entity))
	{
		camera_2d_system::update(m_world, m_camera_entity, *context.input);
	}
	else if (m_world.has<camera_3d>(m_camera_entity))
	{
		camera_3d_system::update(m_world, m_camera_entity, *context.input);
	}

	script_system::after_update(script_context, dt);
	m_world.signals().dispatch(dt);
}

auto noi_engine::scene::render(const scene_context& context) -> void
{
	const auto script_context = to_base_script_context(context, this);
	script_system::before_render(script_context);
	render_system::render(this->m_world, *context.renderer,
						  this->m_camera_entity);
	script_system::after_render(script_context);
}

auto noi_engine::scene::on_enter([[maybe_unused]] const scene_context& context)
	-> void
{
}

auto noi_engine::scene::on_exit([[maybe_unused]] const scene_context& context)
	-> void
{
}

auto noi_engine::scene::on_resize([[maybe_unused]] const scene_context& context,
								  const int width, const int height) -> void
{
	if (m_world.has<camera_2d>(m_camera_entity))
	{
		auto& cam = m_world.get<camera_2d>(m_camera_entity);
		cam.aspect_ratio =
			static_cast<float>(width) / static_cast<float>(height);
	}
	else if (m_world.has<camera_3d>(m_camera_entity))
	{
		auto& cam = m_world.get<camera_3d>(m_camera_entity);
		cam.aspect_ratio =
			static_cast<float>(width) / static_cast<float>(height);
	}
}

auto noi_engine::scene::get_world() -> world&
{
	return this->m_world;
}

auto noi_engine::scene::get_camera_entity() const -> entity
{
	return this->m_camera_entity;
}
