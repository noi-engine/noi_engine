//
// Created by ricka on 8/2/26.
//

#pragma once

#include <span>
#include <noi_engine/core/model/mesh.hpp>

namespace noi_engine
{
    class mesh_loader
    {
    public:
        mesh_loader() = delete;

        [[nodiscard]] static auto load(std::span<const std::byte> data) -> mesh;
    };
}
