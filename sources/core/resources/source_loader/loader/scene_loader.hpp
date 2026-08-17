//
// Created by ricka on 8/16/26.
//

#pragma once

#include <memory>
#include <span>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/resources/resources.hpp>

namespace noi_engine::scene_loader
{
    [[nodiscard]] auto load(resources* resources, std::span<const std::byte> data) -> std::unique_ptr<scene>;
} // namespace noi_engine
