//
// Created by ricka on 8/2/26.
//

#pragma once

#include <glm/mat4x4.hpp>
#include <noi_engine/core/components/transform.hpp>

namespace noi_engine
{
    struct world_matrix
    {
        glm::mat4 value{1.0f};

        [[nodiscard]] static auto from(const transform& transform) -> glm::mat4;
    };
}
