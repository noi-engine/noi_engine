//
// Created by ricka on 9/23/26.
//
#pragma once

#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/system.hpp>

namespace noi_engine
{
    class physics_system : public system
    {
    public:
        static auto step(world& world, float dt) -> void;

        auto on_update(const script_context& ctx, float dt) -> void override;

        [[nodiscard]] auto name() const -> std::string_view override { return "physics_system"; }
    };
}
