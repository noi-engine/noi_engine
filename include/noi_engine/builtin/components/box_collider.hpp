//
// Created by ricka on 9/23/26.
//

#pragma once

#include <glm/vec2.hpp>
#include <noi_engine/core/components/component.hpp>

namespace noi_engine
{
    struct box_collider : component
    {
        glm::vec2 half_extents{0.5f, 0.5f};
        bool is_static{false};
    };
}
