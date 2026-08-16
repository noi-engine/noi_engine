//
// Created by ricka on 8/9/26.
//

#include <noi_engine/builtin/signals/moved_signal.hpp>
#include <noi_engine/core/components/dirty.hpp>
#include <noi_engine/core/components/mesh_renderer.hpp>
#include <noi_engine/core/components/name_component.hpp>
#include <noi_engine/core/components/render_layer.hpp>
#include <noi_engine/core/components/script_component.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/world_matrix.hpp>
#include <noi_engine/core/resources/resource_system.hpp>

#include "../components/player_controller.hpp"
#include "../components/velocity.hpp"
#include "scripts.hpp"

using noi_engine::dirty;
using noi_engine::mesh_renderer;
using noi_engine::moved_signal;
using noi_engine::name_component;
using noi_engine::render_layer;
using noi_engine::script_component;
using noi_engine::transform;
using noi_engine::world_matrix;

auto sandbox::basic::player_script::on_create(
	noi_engine::entity self, const noi_engine::script_context& context) -> void
{
	const auto resources = context.resources;
	add(self, context, velocity{});
	add(self, context, world_matrix{});
	add(self, context, dirty<transform>{});
	add(self, context, render_layer{ .order = 0 });
	add(self, context, player_controller{ .speed = 3.0f });
	add(self, context, transform{ .scale = { 0.8f, 0.8f, 0.8f } });
	add(self, context, name_component{ .name = "player" });

	noi_engine::material green_material;
	green_material.set_shader(
		resources->get_handle<noi_engine::shader>("color_shader"));
	green_material.set_color("u_color", { 0.0f, 1.0f, 0.0f, 1.0f });

	const auto green_material_handle = resources->add(
		std::make_unique<noi_engine::material>(std::move(green_material)));
	add(self, context,
		mesh_renderer{ .m_mesh =
						   resources->get_handle<noi_engine::mesh>("quad_mesh"),
					   .m_material = green_material_handle });
}

auto sandbox::basic::player_script::on_update(
	const noi_engine::entity self, const noi_engine::script_context& context,
	[[maybe_unused]] const float t) -> void
{
	if (has<dirty<transform>>(self, context))
	{
		this->emit(self, context, moved_signal{ self });
	}
}