//
// Created by ricka on 8/2/26.
//

#pragma once

#include <glm/vec3.hpp>
#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/components/component.hpp>

namespace noi_engine
{
    struct follow_target : component
    {
        entity target{};
        glm::vec3 offset{0.0f};
        float smoothing{0.0f};
    };
}
