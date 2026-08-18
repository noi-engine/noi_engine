//
// Created by ricka on 8/18/26.
//

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "mesh_2d_loader.hpp"
#include "fbs/mesh_2d_generated.h"
#include <noi_engine/core/model/vertex.hpp>

auto noi_engine::c::mesh_2d_loader::load(const std::span<const std::byte> data) -> std::unique_ptr<mesh>
{
    const auto fbs = fbs::GetMesh(data.data());
    std::vector indices(fbs->indices()->begin(), fbs->indices()->end());

    std::vector<vertex> vertices{};
    vertices.reserve(fbs->vertices()->size());
    for (const auto fbs_vertex : *fbs->vertices())
    {
        vertex v{};
        if (const auto position = fbs_vertex->position())
        {
            v.position = glm::vec3{position->x(), position->y(), position->z()};
        }

        if (const auto normal = fbs_vertex->normal())
        {
            v.normal = glm::vec3{normal->x(), normal->y(), normal->z()};
        }

        if (const auto uv = fbs_vertex->uv())
        {
            v.uv = glm::vec2{uv->x(), uv->y()};
        }

        vertices.push_back(v);
    }

    return std::make_unique<mesh>(std::move(vertices), std::move(indices));
}
