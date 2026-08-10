//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/scene_manager.hpp>

noi_engine::scene_manager::scene_manager(resource_system* resources) : m_resources(resources)
{
}

auto noi_engine::scene_manager::set_scene(std::unique_ptr<scene> scene) -> void
{
    if (this->m_current)
    {
        this->m_current->on_exit(this->m_resources);
    }
    this->m_current = std::move(scene);
    this->m_current->on_enter(this->m_resources);
}

auto noi_engine::scene_manager::update(const float dt, input_state& input) const -> void
{
    if (this->m_current)
    {
        this->m_current->update(dt, input);
    }
}

auto noi_engine::scene_manager::render(renderer& renderer) const -> void
{
    if (this->m_current)
    {
        this->m_current->render(renderer);
    }
}

auto noi_engine::scene_manager::on_resize(const int width, const int height) const -> void
{
    if (this->m_current)
    {
        this->m_current->on_resize(width, height);
    }
}
