//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <string>
#include <noi_engine/core/renderer/renderer.hpp>
#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/input/input_state.hpp>

namespace noi_engine
{
    class scene
    {
    protected:
        world m_world{};
        std::string m_name{};
        entity m_camera_entity{};

    public:
        explicit scene(std::string name);

        virtual auto render(renderer& renderer) -> void;

        virtual auto update(float dt, const input_state& input) -> void;

        [[nodiscard]] auto get_world() -> world&;

        virtual ~scene() = default;
    };
}
