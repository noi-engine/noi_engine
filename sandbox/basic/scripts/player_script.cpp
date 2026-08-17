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

#include "scripts.hpp"

using noi_engine::dirty;
using noi_engine::mesh_renderer;
using noi_engine::moved_signal;
using noi_engine::name_component;
using noi_engine::render_layer;
using noi_engine::script_component;
using noi_engine::transform;
using noi_engine::world_matrix;

auto sandbox::basic::player_script::on_update(
	const noi_engine::entity self, const noi_engine::script_context& context,
	[[maybe_unused]] const float t) -> void
{
	if (has<dirty<transform>>(self, context))
	{
		this->emit(self, context, moved_signal{ self });
	}
}