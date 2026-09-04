//
// Created by ricka on 8/1/26.
//

#pragma once

#include <vector>
#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/renderer/renderer.hpp>
#include <noi_engine/core/system.hpp>

namespace noi_engine
{
    class render_system : public system
    {
    public:
        static auto render(world& world, renderer& renderer, const entity& active_camera) -> void;

        [[nodiscard]] static auto sorted_renderables(world& world) -> const std::vector<entity>&;

        auto on_render(const script_context& ctx) -> void override;

        [[nodiscard]] auto name() const -> std::string_view override { return "render_system"; }
    };
}
