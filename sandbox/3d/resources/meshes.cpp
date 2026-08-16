//
// Created by ricka on 8/2/26.
//

#include "meshes.hpp"

auto sandbox::threed::meshes::cube() -> noi_engine::mesh
{
    std::vector<noi_engine::vertex> vertices
    {
        // Front (+Z)
        {.position = {-0.5f, -0.5f, 0.5f}, .normal = {0, 0, 1}, .uv = {0, 0}},
        {.position = {0.5f, -0.5f, 0.5f}, .normal = {0, 0, 1}, .uv = {1, 0}},
        {.position = {0.5f, 0.5f, 0.5f}, .normal = {0, 0, 1}, .uv = {1, 1}},
        {.position = {-0.5f, 0.5f, 0.5f}, .normal = {0, 0, 1}, .uv = {0, 1}},

        // Back (-Z)
        {.position = {0.5f, -0.5f, -0.5f}, .normal = {0, 0, -1}, .uv = {0, 0}},
        {.position = {-0.5f, -0.5f, -0.5f}, .normal = {0, 0, -1}, .uv = {1, 0}},
        {.position = {-0.5f, 0.5f, -0.5f}, .normal = {0, 0, -1}, .uv = {1, 1}},
        {.position = {0.5f, 0.5f, -0.5f}, .normal = {0, 0, -1}, .uv = {0, 1}},

        // Right (+X)
        {.position = {0.5f, -0.5f, 0.5f}, .normal = {1, 0, 0}, .uv = {0, 0}},
        {.position = {0.5f, -0.5f, -0.5f}, .normal = {1, 0, 0}, .uv = {1, 0}},
        {.position = {0.5f, 0.5f, -0.5f}, .normal = {1, 0, 0}, .uv = {1, 1}},
        {.position = {0.5f, 0.5f, 0.5f}, .normal = {1, 0, 0}, .uv = {0, 1}},

        // Left (-X)
        {.position = {-0.5f, -0.5f, -0.5f}, .normal = {-1, 0, 0}, .uv = {0, 0}},
        {.position = {-0.5f, -0.5f, 0.5f}, .normal = {-1, 0, 0}, .uv = {1, 0}},
        {.position = {-0.5f, 0.5f, 0.5f}, .normal = {-1, 0, 0}, .uv = {1, 1}},
        {.position = {-0.5f, 0.5f, -0.5f}, .normal = {-1, 0, 0}, .uv = {0, 1}},

        // Top (+Y)
        {.position = {-0.5f, 0.5f, 0.5f}, .normal = {0, 1, 0}, .uv = {0, 0}},
        {.position = {0.5f, 0.5f, 0.5f}, .normal = {0, 1, 0}, .uv = {1, 0}},
        {.position = {0.5f, 0.5f, -0.5f}, .normal = {0, 1, 0}, .uv = {1, 1}},
        {.position = {-0.5f, 0.5f, -0.5f}, .normal = {0, 1, 0}, .uv = {0, 1}},

        // Bottom (-Y)
        {.position = {-0.5f, -0.5f, -0.5f}, .normal = {0, -1, 0}, .uv = {0, 0}},
        {.position = {0.5f, -0.5f, -0.5f}, .normal = {0, -1, 0}, .uv = {1, 0}},
        {.position = {0.5f, -0.5f, 0.5f}, .normal = {0, -1, 0}, .uv = {1, 1}},
        {.position = {-0.5f, -0.5f, 0.5f}, .normal = {0, -1, 0}, .uv = {0, 1}},
    };

    std::vector<uint32_t> indices
    {
        // Front
        0, 1, 2,
        2, 3, 0,

        // Back
        4, 5, 6,
        6, 7, 4,

        // Right
        8, 9, 10,
        10, 11, 8,

        // Left
        12, 13, 14,
        14, 15, 12,

        // Top
        16, 17, 18,
        18, 19, 16,

        // Bottom
        20, 21, 22,
        22, 23, 20
    };
    return noi_engine::mesh(std::move(vertices), std::move(indices));
}
