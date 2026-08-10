//
// Created by ricka on 8/9/26.
//

#include "scripts.hpp"

#include "../components/velocity.hpp"
#include "../components/player_controller.hpp"

#include <noi_engine/core/components/dirty.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/render_layer.hpp>
#include <noi_engine/builtin/signals/moved_signal.hpp>
#include <noi_engine/core/components/mesh_renderer.hpp>
#include <noi_engine/core/components/script_component.hpp>
#include <noi_engine/core/components/world_matrix.hpp>

using noi_engine::dirty;
using noi_engine::transform;
using noi_engine::render_layer;
using noi_engine::world_matrix;
using noi_engine::mesh_renderer;
using noi_engine::script_component;

using noi_engine::moved_signal;

auto sandbox::basic::player_script::on_create() -> void
{
    add(velocity{});
    add(world_matrix{});
    add(dirty<transform>{});
    add(render_layer{.order = 0});
    add(player_controller{.speed = 3.0f});
    add(transform{.scale = {0.8f, 0.8f, 0.8f}});

    noi_engine::material green_material;
    green_material.set_shader(m_color_shader);
    green_material.set_color("u_color", {0.0f, 1.0f, 0.0f, 1.0f});

    const auto green_material_handle = m_resources->add(std::move(green_material));
    add(mesh_renderer{.m_mesh = m_quad_mesh, .m_material = green_material_handle});
}

auto sandbox::basic::player_script::on_update(const float dt) -> void
{
    const auto self = get_self();

    if (has<dirty<transform>>())
    {
        this->emit(moved_signal{self});
    }
}

sandbox::basic::player_script::player_script(noi_engine::resource_system* resources,
                                             const noi_engine::resource_handle<noi_engine::mesh> mesh,
                                             const noi_engine::resource_handle<noi_engine::shader> color_shader)
    : m_resources(resources), m_quad_mesh(mesh), m_color_shader(color_shader)
{
}
