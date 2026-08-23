//
// Created by ricka on 2026-07-30.
//

#include <iostream>
#include <noi_engine/core/renderer/renderer.hpp>
#include <noi_engine/core/resources/resources.hpp>

#include "../glad/glad.h"
#include "noi_engine/core/components/mesh_renderer_properties.hpp"

noi_engine::renderer::renderer(resources& resources)
    : m_resources(resources)
{
}

auto noi_engine::renderer::begin_frame() -> void
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

auto noi_engine::renderer::end_frame() -> void
{
}

auto noi_engine::renderer::draw(const world_matrix& model,
                                const mesh_renderer& mesh_renderer,
                                const glm::mat4& view,
                                const glm::mat4& projection,
                                mesh_renderer_properties* properties) -> void
{
    const auto mesh = m_resources.meshes.get(mesh_renderer.m_mesh);
    const auto material = m_resources.materials.get(mesh_renderer.m_material);
    const auto shader = m_resources.shaders.get(material->shader());

    shader->use();

    shader->set_mat4("u_view", view);
    shader->set_mat4("u_model", model.value);
    shader->set_mat4("u_projection", projection);

    mesh->bind();
    material->apply(*shader, m_resources, properties);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->index_count()),
                   GL_UNSIGNED_INT, nullptr);

    mesh->unbind();
}
