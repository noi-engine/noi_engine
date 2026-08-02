//
// Created by ricka on 8/2/26.
//

#pragma once

#include <span>
#include <noi_engine/core/model/texture.hpp>

namespace noi_engine
{
    class texture_loader
    {
    public:
        texture_loader() = delete;

        static auto load(std::span<const std::byte> data) -> texture;
    };
}
