//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <memory>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/scene_manager.hpp>
#include <noi_engine/core/renderer/renderer.hpp>
#include <noi_engine/core/resources/resource_system.hpp>
#include <noi_engine/core/input/input_state.hpp>

namespace noi_engine
{
    struct game_conf
    {
    };

    class game
    {
        game_conf m_conf{};

        input_state m_input{};
        scene_manager m_scene_manager{};

        std::unique_ptr<renderer> m_renderer{nullptr};
        std::unique_ptr<resource_system> m_resources{nullptr};

    protected:
        virtual auto render() -> void;

        virtual auto update(float dt) -> void;

    public:
        explicit game(const game_conf& conf = {});

        virtual ~game() = default;

        auto set_scene(std::unique_ptr<scene> scene) -> void;

        [[nodiscard]] auto resources() const noexcept -> resource_system&;

        [[nodiscard]] auto input() -> input_state&;

        friend class sdl_game;
    };
}
