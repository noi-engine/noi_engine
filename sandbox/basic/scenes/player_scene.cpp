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

using namespace noi_engine;

sandbox::basic::player_scene::player_scene() : scene("player_scene")
{
	m_world.add<camera_2d>(m_camera_entity,
						   camera_2d{ .orthographic_size = 5.0f });
}

auto sandbox::basic::player_scene::update(const scene_context& context,
										  const float dt) -> void
{
	player_controller_system::update(m_world, *context.input);
	movement_system::update(m_world, dt);

	scene::update(context, dt);
}

void sandbox::basic::player_scene::on_enter(const scene_context& context)
{
	const auto resources = context.resources;
	resources->add("quad_mesh", std::make_unique<mesh>(twod::meshes::quad()));
	resources->add("color_shader",
				   std::make_unique<shader>(twod::shaders::color_shader()));

	const auto player = this->m_world.create_entity();
	const auto camera_script_handle =
		resources->add_script(std::make_unique<camera_script>());
	const auto player_script_handle =
		resources->add_script(std::make_unique<player_script>());
	const auto background_script_handle =
		resources->add_script(std::make_unique<background_script>());

	const auto background = this->m_world.create_entity();
	this->m_world.add(
		background,
		script_component{ .scripts = { background_script_handle } });

	this->m_world.add(player,
					  script_component{ .scripts = { player_script_handle } });

	this->m_world.add(this->get_camera_entity(),
					  script_component{ .scripts = { camera_script_handle } });

	scene::on_enter(context);
}