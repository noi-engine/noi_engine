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
#include <noi_engine/core/assets/asset_provider.hpp>

namespace noi_engine
{
    using opengl_context_loader = void* (*)(const char* name);

    struct game_conf
    {
    };

    class game
    {
        game_conf m_conf{};

        input_state m_input{};

        std::unique_ptr<renderer> m_renderer{nullptr};
        std::unique_ptr<resource_system> m_resources{nullptr};
        std::unique_ptr<scene_manager> m_scene_manager{nullptr};

    protected:
        virtual auto render() -> void;

        virtual auto update(float dt) -> void;

    public:
        explicit game(std::shared_ptr<asset_provider> asset_provider, const game_conf& conf = {});

        virtual ~game() = default;

        auto set_scene(std::unique_ptr<scene> scene) const -> void;

        [[nodiscard]] auto resources() const noexcept -> resource_system&;

        [[nodiscard]] auto input() -> input_state&;

        static auto init(opengl_context_loader loader) -> void;

        friend class sdl_game;
    };
}
