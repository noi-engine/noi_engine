//
// Created by ricka on 8/18/26.
//

#pragma once

#include <span>
#include <memory>
#include <noi_engine/core/model/shader.hpp>
#include <noi_engine/core/resources/resource_loader.hpp>

namespace noi_engine::c::shader_loader
{
    [[nodiscard]] auto load(resource_loader* resources, std::span<const std::byte> data) -> std::unique_ptr<shader>;
}
