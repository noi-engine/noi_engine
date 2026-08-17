//
// Created by ricka on 8/16/26.
//

#pragma once

#include <span>
#include <noi_engine/core/model/mesh.hpp>

namespace noi_engine
{
    class mesh_2d_loader
    {
    public:
        mesh_2d_loader() = delete;

        [[nodiscard]] static auto load(std::span<const std::byte> data) -> mesh;
    };
}