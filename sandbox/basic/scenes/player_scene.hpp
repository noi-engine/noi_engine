//
// Created by ricka on 8/2/26.
//

#pragma once

#include <noi_engine/core/scene.hpp>

namespace sandbox::basic
{
    class player_scene : public noi_engine::scene
    {
    public:
        player_scene();

        auto update(float dt, noi_engine::input_state& input) -> void override;
    };
}
