//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/scene_manager.hpp>

auto noi_engine::scene_manager::set_scene(std::unique_ptr<scene> scene) -> void
{
	this->m_current = std::move(scene);
}

auto noi_engine::scene_manager::update(const float dt) -> void
{
	if (this->m_current)
	{
		this->m_current->update(dt);
	}
}

auto noi_engine::scene_manager::render(renderer &renderer) -> void
{
	if (this->m_current)
	{
		this->m_current->render(renderer);
	}
}