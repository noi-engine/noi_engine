//
// Created by ricka on 8/16/26.
//

#pragma once

#include <span>
#include <memory>
#include <noi_engine/core/model/mesh.hpp>

namespace noi_engine::mesh_2d_loader
{
    [[nodiscard]] auto load(std::span<const std::byte> data) -> std::unique_ptr<mesh>;
}
