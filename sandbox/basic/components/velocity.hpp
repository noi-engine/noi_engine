//
// Created by ricka on 8/2/26.
//

#pragma once

#include <glm/vec3.hpp>
#include <noi_engine/core/components/component.hpp>

namespace sandbox::basic
{
    struct velocity : noi_engine::component
    {
        glm::vec3 value{0.0f};
    };
}
