//
// Created by ricka on 2026-07-30.
//

#include <utility>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/components/camera.hpp>
#include <noi_engine/core/systems/render_system.hpp>

noi_engine::scene::scene(std::string name) : m_name(std::move(name))
{
    this->m_camera_entity = this->m_world.create_entity();
    this->m_world.add(this->m_camera_entity, camera{});
    this->m_world.add(this->m_camera_entity, transform{.position = {0.0f, 0.0f, 0.4f}});
}

auto noi_engine::scene::render(renderer& renderer) -> void
{
    render_system::render(this->m_world, renderer, this->m_camera_entity);
}

auto noi_engine::scene::update(float dt) -> void
{
}

auto noi_engine::scene::get_world() -> world&
{
    return this->m_world;
}
