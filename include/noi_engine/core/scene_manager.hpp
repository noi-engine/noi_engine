//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <memory>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/renderer/renderer.hpp>
#include <noi_engine/core/input/input_state.hpp>

namespace noi_engine
{
    class scene_manager
    {
        resource_system* m_resources{nullptr};
        std::unique_ptr<scene> m_current{nullptr};

    public:
        scene_manager(resource_system *resources);

        virtual ~scene_manager() = default;

        auto set_scene(std::unique_ptr<scene> scene) -> void;

        auto update(float dt, input_state& input) const -> void;

        auto render(renderer& renderer) const -> void;

        auto on_resize(int width, int height) const -> void;
    };
}
