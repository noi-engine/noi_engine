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
	struct scene_context
	{
		renderer* renderer{nullptr};
		input_state* input{nullptr};
		resource_system* resources{nullptr};
	};

    class scene
    {
    protected:
        world m_world{};
        std::string m_name{};
        entity m_camera_entity{};

    public:
        explicit scene(std::string name);

        virtual auto render(const scene_context& context) -> void;

        virtual auto on_enter(const scene_context& context) -> void;
        virtual auto on_exit(const scene_context& context) -> void;

        virtual auto update(const scene_context& context, float dt) -> void;

        virtual auto on_resize(const scene_context& context, int width, int height) -> void;

        [[nodiscard]] auto get_world() -> world&;

        [[nodiscard]] auto get_camera_entity() const -> entity;

        virtual ~scene() = default;
    };
}
