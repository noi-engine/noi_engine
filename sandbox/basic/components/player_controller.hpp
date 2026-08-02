//
// Created by ricka on 8/2/26.
//

#pragma once

#include <noi_engine/core/components/component.hpp>

namespace sandbox::basic
{
    struct player_controller : noi_engine::component
    {
        float speed{3.0f};
    };
}