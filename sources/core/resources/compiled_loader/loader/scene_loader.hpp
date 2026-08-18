//
// Created by ricka on 8/18/26.
//

#pragma once

#include <span>
#include <memory>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/resources/resources.hpp>

namespace noi_engine::c::scene_loader
{
    [[nodiscard]] auto load(resources* resources, std::span<const std::byte> data) -> std::unique_ptr<scene>;
}
