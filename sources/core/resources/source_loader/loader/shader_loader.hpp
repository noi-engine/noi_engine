//
// Created by ricka on 8/16/26.
//

#pragma once

#include <memory>
#include <noi_engine/core/model/shader.hpp>
#include <noi_engine/core/resources/resource_loader.hpp>
#include <span>

namespace noi_engine::shader_loader
{
    [[nodiscard]] auto load(resource_loader* resource_loader,
                            std::span<const std::byte> data) -> std::unique_ptr<shader>;
} // namespace noi_engine
