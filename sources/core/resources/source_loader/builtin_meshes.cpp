//
// Created by ricka on 8/23/26.
//

#include "builtin_meshes.hpp"
#include <memory>

namespace noi_engine
{
    static auto load_quad_2d() -> std::unique_ptr<mesh>
    {
        std::vector<vertex> vertices
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

        return std::make_unique<mesh>(std::move(vertices), std::move(indices));
    }

    auto builtin_meshes::load(const std::string_view name, [[maybe_unused]] resources* resources) -> std::unique_ptr<mesh>
    {
        static const std::unordered_map<std::string_view, std::function<std::unique_ptr<mesh>()>> loaders = {
            {NOI_ENGINE_BUILTIN_QUAD_2D_MESH_NAME, &load_quad_2d},
        };

        if (const auto it = loaders.find(name); it != loaders.end())
        {
            return it->second();
        }

        return nullptr;
    }
} // namespace noi_engine
