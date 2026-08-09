//
// Created by ricka on 8/9/26.
//

#pragma once

#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/signals/signal.hpp>

namespace noi_engine
{
    struct moved_signal : signal
    {
        explicit moved_signal(const entity& entity) : signal(entity)
        {
        }
    };
}
