//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <glm/mat4x4.hpp>
#include <noi_engine/core/components/mesh_renderer.hpp>
#include <noi_engine/core/components/world_matrix.hpp>
#include <noi_engine/core/resources/resource_system.hpp>

namespace noi_engine
{
    class renderer
    {
    protected:
        resource_system& m_resources;

    public:
        explicit renderer(resource_system& resources);

        virtual ~renderer() = default;

        static auto begin_frame() -> void;

        static auto end_frame() -> void;

        auto draw(const world_matrix& transform, const mesh_renderer& mesh_renderer, const glm::mat4& view, const glm::mat4& projection) -> void;
    };
}
