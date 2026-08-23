#pragma once

#include <noi_engine/core/components/component.hpp>

namespace noi_engine
{
    struct camera_2d : component
    {
        float zoom{1.0f};
        float near_plane{-1.0f};
        float far_plane{1.0f};
        float aspect_ratio{16.0f / 9.0f};
        float orthographic_size{4.5f};
    };
}
