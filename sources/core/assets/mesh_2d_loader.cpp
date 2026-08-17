//
// Created by ricka on 8/16/26.
//

#include "mesh_2d_loader.hpp"
#include <nlohmann/json.hpp>

auto noi_engine::mesh_2d_loader::load(std::span<const std::byte> data) -> mesh
{
    const auto root_json = nlohmann::json::parse(data.begin(), data.end());

    std::vector<uint32_t> indices = root_json["indices"];
    std::vector<vertex> vertices{};

    if (root_json.contains("vertices") && root_json["vertices"].is_array())
    {
        vertices.reserve(root_json["vertices"].size());

        for (const auto& v_json : root_json["vertices"])
        {
            vertex v{};

            if (v_json.contains("position"))
            {
                const auto& pos = v_json["position"];
                v.position = glm::vec3{pos[0], pos[1], pos[2]};
            }

            if (v_json.contains("normal"))
            {
                const auto& norm = v_json["normal"];
                v.normal = glm::vec3{norm[0], norm[1], norm[2]};
            }

            if (v_json.contains("uv"))
            {
                const auto& uv = v_json["uv"];
                v.uv = glm::vec2{uv[0], uv[1]};
            }

            vertices.push_back(v);
        }
    }

    return mesh(std::move(vertices), std::move(indices));
}
