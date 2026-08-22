//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/scene_manager.hpp>

noi_engine::scene_manager::scene_manager(const scene_context& context)
	: m_context(std::move(context))
{
}

auto noi_engine::scene_manager::set_scene(std::unique_ptr<scene> scene) -> void
{
	if (this->m_current)
	{
		this->m_current->on_exit(this->m_context);
	}
	this->m_current = std::move(scene);
	this->m_current->on_enter(this->m_context);
}

auto noi_engine::scene_manager::update(const float dt) const -> void
{
	if (this->m_current)
	{
		this->m_current->update(this->m_context, dt);
	}
}

auto noi_engine::scene_manager::render() const -> void
{
	if (this->m_current)
	{
		this->m_current->render(this->m_context);
	}
}

auto noi_engine::scene_manager::current() const -> scene*
{
	if (this->m_current)
	{
		return this->m_current.get();
	}
	return nullptr;
}

auto noi_engine::scene_manager::on_resize(const int width,
                                          const int height) const -> void
{
	if (this->m_current)
	{
		this->m_current->on_resize(this->m_context, width, height);
	}
}
