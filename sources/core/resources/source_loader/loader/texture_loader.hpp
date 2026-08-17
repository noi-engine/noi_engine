//
// Created by ricka on 8/2/26.
//

#pragma once

#include <span>
#include <memory>
#include <noi_engine/core/model/texture.hpp>

namespace noi_engine::texture_loader
{
    [[nodiscard]] auto load(std::span<const std::byte> data) -> std::unique_ptr<texture>;
}
