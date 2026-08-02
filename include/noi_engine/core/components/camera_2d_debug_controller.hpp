//
// Created by ricka on 8/2/26.
//

#pragma once

#include <noi_engine/core/components/component.hpp>

namespace noi_engine
{
    struct camera_2d_debug_controller : component
    {
        float pan_sensitivity{1.0f};
        float zoom_speed{0.1f};
        float min_zoom{0.1f};
        float max_zoom{10.0f};
    };
}
