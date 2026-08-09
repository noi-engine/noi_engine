//
// Created by ricka on 8/9/26.
//

#pragma once

#include <glm/vec3.hpp>
#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/builtin/actions/action_context.hpp>

namespace noi_engine::actions
{
    struct follow_actions_params
    {
        entity target{};
        entity follower{};
        glm::vec3 offset{0.0f};
        float smoothing{0.0f};
    };

    auto follow(const action_context& context, const follow_actions_params& params) -> void;
}
