//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/game.hpp>

#include "glad/glad.h"
#include <noi_engine/core/model/shader.hpp>

#include "resources/source_loader/builtin_shaders.hpp"
#include "resources/source_loader/builtin_meshes.hpp"
#include "resources/source_loader/builtin_materials.hpp"

auto noi_engine::game::render() -> void
{
    this->m_scene_manager->render();
}

auto noi_engine::game::update(const float dt) -> void
{
    this->m_scene_manager->update(dt);
}

auto noi_engine::game::init_builtin_resources() -> void
{
    m_resources->load_from_path<mesh>(NOI_ENGINE_BUILTIN_QUAD_2D_MESH_NAME, NOI_ENGINE_BUILTIN_QUAD_2D_MESH_NAME);
    m_resources->load_from_path<shader>(NOI_ENGINE_BUILTIN_COLOR_SHADER_NAME, NOI_ENGINE_BUILTIN_COLOR_SHADER_NAME);
    m_resources->load_from_path<shader>(NOI_ENGINE_BUILTIN_TEXTURE_SHADER_NAME, NOI_ENGINE_BUILTIN_TEXTURE_SHADER_NAME);
    m_resources->load_from_path<material>(NOI_ENGINE_BUILTIN_COLOR_MATERIAL_NAME, NOI_ENGINE_BUILTIN_COLOR_MATERIAL_NAME);
    m_resources->load_from_path<material>(NOI_ENGINE_BUILTIN_TEXTURE_MATERIAL_NAME, NOI_ENGINE_BUILTIN_TEXTURE_MATERIAL_NAME);
}

noi_engine::game::game(std::unique_ptr<resource_loader> resource_loader,
                       const game_conf& conf)
    : m_conf(conf)
{
    this->m_resources = std::make_unique<noi_engine::resources>(std::move(resource_loader));
    this->m_renderer = std::make_unique<renderer>(*this->m_resources);

    const scene_context context{
        .game = this,
        .renderer = this->m_renderer.get(),
        .input = &this->m_input,
        .resources = this->m_resources.get()
    };
    this->m_scene_manager = std::make_unique<scene_manager>(std::move(context));
}

auto noi_engine::game::set_scene(std::unique_ptr<scene> scene) const -> void
{
    this->m_scene_manager->set_scene(std::move(scene));
}

auto noi_engine::game::resources() const noexcept -> noi_engine::resources&
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

    // TODO: check if necessary
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
