//
// Created by ricka on 8/9/26.
//

#pragma once

#include <noi_engine/core/ecs/entity.hpp>

namespace noi_engine
{
    struct signal
    {
        entity source;

        signal() = delete;

        constexpr explicit signal(const entity src) : source(src)
        {
        }
    };
}
