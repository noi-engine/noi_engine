//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <noi_engine/core/input/input_state.hpp>
#include <noi_engine/core/renderer/renderer.hpp>
#include <noi_engine/core/resources/resource_loader.hpp>
#include <noi_engine/core/resources/resources.hpp>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/scene_manager.hpp>
#include <string_view>

//TODO(begin): no idea
// Inside a script: go to another scene ("scenes/level2.scene") after this frame.
#define NOI_ENGINE_LOAD_SCENE(Path) \
    context.game->request_scene(Path)

#define NOI_ENGINE_REGISTER_SCRIPT(Type) \
    game.register_script<Type>(#Type)

#define NOI_ENGINE_REGISTER_SCRIPT_PTR(Type) \
    game->register_script<Type>(#Type)

#define NOI_ENGINE_REGISTER_SCRIPT_NAMED(Type, Name) \
    game.register_script<Type>(Name)
//TODO(end): no idea

namespace noi_engine
{
    using opengl_context_loader = void* (*)(const char* name);

    struct game_conf
    {
    };

    class game
    {
        static inline game* s_instance{nullptr};

        std::unique_ptr<renderer> m_renderer{nullptr};
        std::unique_ptr<resources> m_resources{nullptr};
        // Scene asked for by a script, loaded once the current frame's update is over.
        std::string m_requested_scene;
        std::function<void(scene&)> m_on_scene_loaded;

    protected:
        game_conf m_conf{};
        input_state m_input{};
        std::unique_ptr<scene_manager> m_scene_manager{nullptr};

        virtual auto render() -> void;

        virtual auto update(float dt) -> void;

        virtual auto init_builtin_resources() const -> void;

    public:
        explicit game(std::unique_ptr<resource_loader> resource_loader, const game_conf& conf = {});

        virtual ~game();

        [[nodiscard]] static auto instance() -> game*;

        auto set_scene(std::unique_ptr<scene> scene) const -> void;

        auto set_scene(std::string_view path) const -> void;

        // Switches to another scene at the end of the current frame. Safe to call from a script
        // (set_scene would destroy the scene that is still running its update).
        auto request_scene(std::string path) -> void;

        // Called with every scene loaded from a path (set_scene(path), request_scene): the place
        // to add the systems a scene needs, since they aren't part of the scene file.
        auto on_scene_loaded(std::function<void(scene&)> callback) -> void;

        template <typename T>
        auto register_script(const std::string_view name) const -> void
        {
            this->m_resources->register_script<T>(name);
        }

        [[nodiscard]] auto resources() const noexcept -> resources&;

        [[nodiscard]] auto input() -> input_state&;

        static auto init(opengl_context_loader loader) -> void;
    };
} // namespace noi_engine
