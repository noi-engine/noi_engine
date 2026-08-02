//
// Created by ricka on 8/1/26.
//

#pragma once

#include <noi_engine/core/components/component.hpp>

namespace noi_engine
{
    struct camera_3d: component
    {
        float fov{45.0f};
        float near_plane{0.1f};
        float far_plane{1000.0f};
        float aspect_ratio{16.0f / 9.0f};
    };
}
