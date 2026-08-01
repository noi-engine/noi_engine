//
// Created by ricka on 8/1/26.
//

#pragma once

#include <cstdint>
#include <vector>
#include <noi_engine/core/model/vertex.hpp>

namespace noi_engine
{
    class mesh_data
    {
        std::vector<vertex> m_vertices{};
        std::vector<uint32_t> m_indices{};
        uint32_t m_vao{ 0 };
        uint32_t m_vbo{ 0 };
        uint32_t m_ebo{ 0 };

    public:
        explicit mesh_data(std::vector<vertex> vertices, std::vector<uint32_t> indices);

        ~mesh_data();

        mesh_data(const mesh_data&) = delete;

        auto operator=(const mesh_data&) -> mesh_data& = delete;

        mesh_data(mesh_data&& other) noexcept;

        auto operator=(mesh_data&& other) noexcept -> mesh_data&;

        auto upload() -> void;

        [[nodiscard]] auto vao() const noexcept -> uint32_t;

        [[nodiscard]] auto index_count() const noexcept -> uint32_t;
    };
}