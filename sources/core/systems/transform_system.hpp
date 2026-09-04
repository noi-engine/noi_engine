//
// Created by ricka on 8/2/26.
//
#pragma once

#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/system.hpp>

namespace noi_engine
{
    class transform_system : public system
    {
    public:
        static auto sync(world& world) -> void;

        auto on_update(const script_context& ctx, float dt) -> void override;

        [[nodiscard]] auto name() const -> std::string_view override { return "transform_system"; }
    };
}