//
// Created by ricka on 8/2/26.
//

#include "mesh_loader.hpp"

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <tiny_obj_loader.h>

namespace
{
    struct vertex_key
    {
        int position;
        int normal;
        int uv;

        [[nodiscard]] auto operator==(const vertex_key& other) const -> bool
        {
            return position == other.position && normal == other.normal && uv == other.uv;
        }
    };

    struct vertex_key_hash
    {
        [[nodiscard]] auto operator()(const vertex_key& key) const -> std::size_t
        {
            return (static_cast<std::size_t>(key.position) * 73856093) ^
                (static_cast<std::size_t>(key.normal) * 19349663) ^
                (static_cast<std::size_t>(key.uv) * 83492791);
        }
    };
}

auto noi_engine::mesh_loader::load(const std::span<const std::byte> data) -> mesh
{
    const std::string text(reinterpret_cast<const char*>(data.data()), data.size());

    tinyobj::ObjReaderConfig config;
    config.triangulate = true;

    tinyobj::ObjReader reader;

    if (!reader.ParseFromString(text, "", config))
    {
        throw std::runtime_error(reader.Error());
    }

    const auto& attrib = reader.GetAttrib();
    const auto& shapes = reader.GetShapes();

    std::vector<vertex> vertices;
    std::vector<uint32_t> indices;
    std::unordered_map<vertex_key, uint32_t, vertex_key_hash> unique_vertices;

    for (const auto& shape : shapes)
    {
        for (const auto& index : shape.mesh.indices)
        {
            const vertex_key key{index.vertex_index, index.normal_index, index.texcoord_index};

            const auto it = unique_vertices.find(key);

            if (it != unique_vertices.end())
            {
                indices.push_back(it->second);
                continue;
            }

            vertex v{};

            if (index.vertex_index >= 0)
            {
                v.position = {
                    attrib.vertices[3 * static_cast<std::size_t>(index.vertex_index) + 0],
                    attrib.vertices[3 * static_cast<std::size_t>(index.vertex_index) + 1],
                    attrib.vertices[3 * static_cast<std::size_t>(index.vertex_index) + 2]
                };
            }

            if (index.normal_index >= 0)
            {
                v.normal = {
                    attrib.normals[3 * static_cast<std::size_t>(index.normal_index) + 0],
                    attrib.normals[3 * static_cast<std::size_t>(index.normal_index) + 1],
                    attrib.normals[3 * static_cast<std::size_t>(index.normal_index) + 2]
                };
            }

            if (index.texcoord_index >= 0)
            {
                v.uv = {
                    attrib.texcoords[2 * static_cast<std::size_t>(index.texcoord_index) + 0],
                    attrib.texcoords[2 * static_cast<std::size_t>(index.texcoord_index) + 1]
                };
            }

            const auto new_index = static_cast<uint32_t>(vertices.size());
            vertices.push_back(v);
            unique_vertices[key] = new_index;
            indices.push_back(new_index);
        }
    }

    return mesh(std::move(vertices), std::move(indices));
}
