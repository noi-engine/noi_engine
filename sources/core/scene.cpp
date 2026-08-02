//
// Created by ricka on 2026-07-30.
//

#include <utility>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/systems/render_system.hpp>
#include <noi_engine/core/systems/camera_3d_system.hpp>
#include <noi_engine/core/systems/camera_2d_system.hpp>
#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/camera_3d.hpp>

#include "noi_engine/core/components/world_matrix.hpp"
#include "noi_engine/core/systems/transform_system.hpp"

noi_engine::scene::scene(std::string name) : m_name(std::move(name))
{
    this->m_camera_entity = m_world.create_entity();
    m_world.add(m_camera_entity, transform{});
    m_world.add(m_camera_entity, world_matrix{});
}

auto noi_engine::scene::render(renderer& renderer) -> void
{
    render_system::render(this->m_world, renderer, this->m_camera_entity);
}

auto noi_engine::scene::update(float dt, const input_state& input) -> void
{
    transform_system::sync(m_world);

    if (m_world.has<camera_2d>(m_camera_entity))
    {
        camera_2d_system::update(m_world, m_camera_entity, input);
    }
    else if (m_world.has<camera_3d>(m_camera_entity))
    {
        camera_3d_system::update(m_world, m_camera_entity, input);
    }
}

auto noi_engine::scene::on_resize(const int width, const int height) -> void
{
    if (m_world.has<camera_2d>(m_camera_entity))
    {
        auto& cam = m_world.get<camera_2d>(m_camera_entity);
        cam.aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
    }
    else if (m_world.has<camera_3d>(m_camera_entity))
    {
        auto& cam = m_world.get<camera_3d>(m_camera_entity);
        cam.aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
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
