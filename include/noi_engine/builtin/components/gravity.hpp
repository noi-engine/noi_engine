//
// Created by ricka on 9/23/26.
//

#pragma once

#include <glm/vec2.hpp>
#include <noi_engine/core/components/component.hpp>

namespace noi_engine
{
    struct gravity : component
    {
        glm::vec2 acceleration{0.0f, -9.81f};
        glm::vec2 velocity{0.0f, 0.0f};
        bool enabled{true};
        // Not saved: set by physics_system each step, true when the body rests on something solid.
        // Use it for "can jump".
        bool grounded{false};
    };
}
