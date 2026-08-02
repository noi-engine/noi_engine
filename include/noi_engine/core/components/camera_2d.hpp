//
// Created by ricka on 8/2/26.
//

#pragma once

#include <glm/vec2.hpp>

namespace noi_engine
{
    struct camera_2d
    {
        glm::vec2 position{0.0f};
        float zoom{1.0f};
        float near_plane{-1.0f};
        float far_plane{1.0f};
        float aspect_ratio{16.0f / 9.0f};
        float orthographic_size{5.0f};
        float pan_sensitivity{1.0f};
        float zoom_speed{0.1f};
        float min_zoom{0.1f};
        float max_zoom{10.0f};
    };
}
