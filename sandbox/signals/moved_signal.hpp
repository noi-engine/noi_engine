//
// Created by ricka on 8/9/26.
//

#pragma once

#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/signals/signal.hpp>

namespace sandbox
{
    struct moved_signal : noi_engine::signal
    {
        explicit moved_signal(const noi_engine::entity& entity) : signal(entity)
        {
        }
    };
}
