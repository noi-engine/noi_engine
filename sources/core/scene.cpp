//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/scene.hpp>
#include <utility>

noi_engine::scene::scene(std::string name) : m_name(std::move(name))
{
}

auto noi_engine::scene::render(renderer& renderer) -> void
{
}

auto noi_engine::scene::update(float dt) -> void
{
}

auto noi_engine::scene::get_world() -> world&
{
	return this->m_world;
}