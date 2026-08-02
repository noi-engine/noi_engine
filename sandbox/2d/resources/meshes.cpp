//
// Created by ricka on 8/2/26.
//

#include "meshes.hpp"

auto sandbox::twod::meshes::quad() -> noi_engine::mesh
{
    std::vector<noi_engine::vertex> vertices
    {
        // Position              Normal        UV
        {.position = {-0.5f, -0.5f, 0.0f}, .normal = {0, 0, 1}, .uv = {0, 0}},
        {.position = {0.5f, -0.5f, 0.0f}, .normal = {0, 0, 1}, .uv = {1, 0}},
        {.position = {0.5f, 0.5f, 0.0f}, .normal = {0, 0, 1}, .uv = {1, 1}},
        {.position = {-0.5f, 0.5f, 0.0f}, .normal = {0, 0, 1}, .uv = {0, 1}},
    };

    std::vector<uint32_t> indices
    {
        0, 1, 2,
        2, 3, 0
    };

    noi_engine::mesh mesh(
        std::move(vertices),
        std::move(indices)
    );

    mesh.upload();

    return mesh;
}
