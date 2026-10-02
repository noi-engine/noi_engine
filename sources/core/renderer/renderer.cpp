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
    // Re-asserted every frame, not just once at init: embedding hosts (e.g. the editor's Qt
    // viewport) run their own GL work on this context between frames and don't promise to leave
    // blending enabled, so a one-time glEnable would silently stop taking effect there - sprites'
    // transparent pixels would composite as opaque black instead of blending with what's behind.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
    if (!mesh || !material)
    {
        // Unassigned/stale mesh or material handle (e.g. edited to an empty/unknown resource
        // reference) - nothing sane to draw, skip this entity rather than dereferencing null.
        return;
    }

    const auto shader = m_resources.shaders.get(material->shader());
    if (!shader)
    {
        return;
    }

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
