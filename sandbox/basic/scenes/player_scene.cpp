//
// Created by ricka on 8/2/26.
//

#include "player_scene.hpp"

#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/script_component.hpp>

#include "../../2d/resources/meshes.hpp"
#include "../../2d/resources/shaders.hpp"
#include "../scripts/scripts.hpp"
#include "../systems/movement_system.hpp"
#include "../systems/player_controller_system.hpp"

sandbox::basic::player_scene::player_scene() : scene("player_scene")
{
	m_world.add<noi_engine::camera_2d>(
		m_camera_entity, noi_engine::camera_2d{ .orthographic_size = 5.0f });
}

auto sandbox::basic::player_scene::update(
	const noi_engine::scene_context& context, const float dt) -> void
{
	player_controller_system::update(m_world, *context.input);
	movement_system::update(m_world, dt);

	scene::update(context, dt);
}

void sandbox::basic::player_scene::on_enter(
	const noi_engine::scene_context& context)
{
	auto resources = context.resources;
	this->m_quad_mesh = resources->add(twod::meshes::quad());
	this->m_color_shader = resources->add(twod::shaders::color_shader());

	const auto background = this->m_world.create_entity();
	this->m_world.add(background,
					  noi_engine::script_component{
						  .instance = std::make_shared<background_script>(
							  resources, m_quad_mesh, m_color_shader) });

	const auto player = this->m_world.create_entity();
	this->m_world.add(player,
					  noi_engine::script_component{
						  .instance = std::make_shared<player_script>(
							  resources, m_quad_mesh, m_color_shader) });

	this->m_world.add(
		this->get_camera_entity(),
		noi_engine::script_component{
			.instance = std::make_shared<camera_script>(player) });

	scene::on_enter(context);
}
