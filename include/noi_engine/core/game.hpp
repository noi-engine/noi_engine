//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <memory>
#include <noi_engine/core/window.hpp>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/scene_manager.hpp>
#include <noi_engine/core/renderer/renderer.hpp>
#include <noi_engine/core/resources/resource_system.hpp>
#include <noi_engine/core/input/input_state.hpp>

namespace noi_engine
{
    struct game_conf
    {
        int max_fps{60};
        bool v_sync{true};
    };

    class game
    {
        game_conf m_conf{};
        bool m_running{false};

        input_state m_input{};
        resource_system m_resources{};
        scene_manager m_scene_manager{};

        std::unique_ptr<window> m_window{nullptr};
        std::unique_ptr<renderer> m_renderer{nullptr};

    protected:
        virtual auto render() -> void;

        virtual auto process_events() -> void;

        virtual auto update(float dt) -> void;

    public:
        explicit game(const std::string& title, int width, int height,
                      const game_conf& conf = game_conf());

        virtual ~game();

        auto set_scene(std::unique_ptr<scene> scene) -> void;

        [[nodiscard]] auto get_window() -> window&;

        [[nodiscard]] auto get_window() const -> const window&;

        [[nodiscard]] auto resources() noexcept -> resource_system&;

        [[nodiscard]] auto input() -> input_state&;

        virtual auto run(int argc, char** argv) -> int;
    };
}
