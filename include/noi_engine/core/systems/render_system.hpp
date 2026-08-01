//
// Created by ricka on 8/1/26.
//

#pragma once

#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/renderer/renderer.hpp>

namespace noi_engine
{
    class render_system
    {
    public:
        render_system() = delete;

        static auto render(world& world, renderer& renderer, const entity &active_camera) -> void;
    };
}
