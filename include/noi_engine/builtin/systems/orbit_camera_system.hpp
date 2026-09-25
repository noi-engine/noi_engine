//
// Created by ricka on 8/1/26.
//

#pragma once

#include <glm/mat4x4.hpp>
#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/input/input_state.hpp>
#include <noi_engine/core/system.hpp>

namespace noi_engine
{
    class orbit_camera_system : public system
    {
    public:
        static auto update(world& world, entity camera_entity, const input_state& input) -> void;

        [[nodiscard]] static auto view_matrix(world& world, entity camera_entity) -> glm::mat4;

        auto on_update(const script_context& ctx, float dt) -> void override;

        [[nodiscard]] auto name() const -> std::string_view override { return "orbit_camera_system"; }
    };
}
