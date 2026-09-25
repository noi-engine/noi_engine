//
// Created by ricka on 8/1/26.
//

#pragma once

#include <glm/vec3.hpp>
#include <noi_engine/core/components/component.hpp>

namespace noi_engine
{
    struct orbit_camera : component
    {
        glm::vec3 target{0.0f};
        float distance{5.0f};
        float yaw{0.0f};
        float pitch{0.2f};
        float sensitivity{0.3f};
        float zoom_speed{1.0f};
        float min_distance{1.0f};
        float max_distance{50.0f};
        float min_pitch{-1.5f};
        float max_pitch{1.5f};
    };
}
