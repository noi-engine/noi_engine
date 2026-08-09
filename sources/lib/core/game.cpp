//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/game.hpp>

#include "glad/glad.h"
#include "assets/filesystem_asset_provider.hpp"

auto noi_engine::game::render() -> void
{
    this->m_scene_manager.render(*this->m_renderer);
}

auto noi_engine::game::update(const float dt) -> void
{
    this->m_scene_manager.update(dt, m_input);
}

noi_engine::game::game(const game_conf& conf)
    : m_conf(conf)
{
    this->m_resources =
        std::make_unique<resource_system>(
            std::make_unique<filesystem_asset_provider>(
                std::filesystem::current_path()
            )
        ); //TODO: should be another provider on release
    this->m_renderer = std::make_unique<renderer>(*this->m_resources);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

auto noi_engine::game::set_scene(std::unique_ptr<scene> scene) -> void
{
    this->m_scene_manager.set_scene(std::move(scene));
}

auto noi_engine::game::resources() const noexcept -> resource_system&
{
    return *this->m_resources;
}

auto noi_engine::game::input() -> input_state&
{
    return this->m_input;
}
