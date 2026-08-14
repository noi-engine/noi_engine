//
// Created by ricka on 2026-07-30.
//

#include "glad/glad.h"
#include <noi_engine/core/game.hpp>

auto noi_engine::game::render() -> void
{
    this->m_scene_manager->render(*this->m_renderer);
}

auto noi_engine::game::update(const float dt) -> void
{
    this->m_scene_manager->update(dt, m_input);
}

noi_engine::game::game(std::shared_ptr<asset_provider> asset_provider, const game_conf& conf)
    : m_conf(conf)
{
    this->m_resources = std::make_unique<resource_system>(asset_provider);
    this->m_renderer = std::make_unique<renderer>(*this->m_resources);
    this->m_scene_manager = std::make_unique<scene_manager>(this->m_resources.get());
}

auto noi_engine::game::set_scene(std::unique_ptr<scene> scene) -> void
{
    this->m_scene_manager->set_scene(std::move(scene));
}

auto noi_engine::game::resources() const noexcept -> resource_system&
{
    return *this->m_resources;
}

auto noi_engine::game::input() -> input_state&
{
    return this->m_input;
}

auto noi_engine::game::init(const opengl_context_loader loader) -> void
{
    if (gladLoadGLLoader(loader) == 0)
    {
        throw std::runtime_error("Failed to initialize OpenGL");
    }

    //TODO: check if necessary
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
