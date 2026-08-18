//
// Created by ricka on 8/18/26.
//

#pragma once

#include <span>
#include <memory>
#include <noi_engine/core/resources/resource_loader.hpp>

namespace noi_engine::c::mesh_2d_loader
{
    [[nodiscard]] auto load(std::span<const std::byte> data) -> std::unique_ptr<mesh>;
}
