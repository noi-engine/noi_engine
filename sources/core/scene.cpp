//
// Created by ricka on 2026-07-30.
//

#include <utility>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/components/camera.hpp>
#include <noi_engine/core/systems/render_system.hpp>
#include <noi_engine/core/components/orbit_camera.hpp>
#include <noi_engine/core/systems/orbit_camera_system.hpp>

noi_engine::scene::scene(std::string name) : m_name(std::move(name))
{
    m_camera_entity = m_world.create_entity();
    m_world.add(m_camera_entity, camera{});
    m_world.add(m_camera_entity, transform{});
    m_world.add(m_camera_entity, orbit_camera{.target = {0.0f, 0.0f, 0.0f}, .distance = 5.0f});
}

auto noi_engine::scene::render(renderer& renderer) -> void
{
    render_system::render(this->m_world, renderer, this->m_camera_entity);
}

auto noi_engine::scene::update(float dt, const input_state& input) -> void
{
    if (m_world.pool<orbit_camera>().has(m_camera_entity))
    {
        orbit_camera_system::update(m_world, m_camera_entity, input);
    }
}

auto noi_engine::scene::get_world() -> world&
{
    return this->m_world;
}
