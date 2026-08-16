//
// Created by ricka on 8/9/26.
//

#include <noi_engine/builtin/signals/moved_signal.hpp>
#include <noi_engine/core/components/dirty.hpp>
#include <noi_engine/core/components/mesh_renderer.hpp>
#include <noi_engine/core/components/render_layer.hpp>
#include <noi_engine/core/components/script_component.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/world_matrix.hpp>
#include <noi_engine/core/resources/resource_system.hpp>

#include "scripts.hpp"

using noi_engine::dirty;
using noi_engine::mesh_renderer;
using noi_engine::render_layer;
using noi_engine::script_component;
using noi_engine::transform;
using noi_engine::world_matrix;

using noi_engine::moved_signal;

auto sandbox::basic::background_script::on_create(
	const noi_engine::entity self, const noi_engine::script_context& context)
	-> void
{
	const auto resources = context.resources;
	add(self, context, world_matrix{});
	add(self, context, render_layer{ .order = -1 });
	add(self, context, transform{ .scale = { 8.0f, 8.0f, 1.0f } });
	add(self, context, transform{ .scale = { 0.8f, 0.8f, 0.8f } });

	noi_engine::material background_material;
	background_material.set_shader(
		resources->get_handle<noi_engine::shader>("color_shader"));
	background_material.set_color("u_color", { 0.15f, 0.15f, 0.2f, 1.0f });
	const auto background_material_handle = resources->add(
		std::make_unique<noi_engine::material>(std::move(background_material)));

	add(self, context,
		mesh_renderer{ .m_mesh =
						   resources->get_handle<noi_engine::mesh>("quad_mesh"),
					   .m_material = background_material_handle });
}