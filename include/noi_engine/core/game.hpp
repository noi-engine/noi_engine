//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <memory>
#include <noi_engine/core/input/input_state.hpp>
#include <noi_engine/core/renderer/renderer.hpp>
#include <noi_engine/core/resources/resource_loader.hpp>
#include <noi_engine/core/resources/resources.hpp>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/scene_manager.hpp>
#include <string_view>

//TODO(begin): no idea
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
        std::unique_ptr<renderer> m_renderer{nullptr};
        std::unique_ptr<resources> m_resources{nullptr};

    protected:
        game_conf m_conf{};
        input_state m_input{};
        std::unique_ptr<scene_manager> m_scene_manager{nullptr};

        virtual auto render() -> void;

        virtual auto update(float dt) -> void;

        virtual auto init_builtin_resources() const -> void;

    public:
        explicit game(std::unique_ptr<resource_loader> resource_loader, const game_conf& conf = {});

        virtual ~game() = default;

        auto set_scene(std::unique_ptr<scene> scene) const -> void;

        auto set_scene(std::string_view path) const -> void;

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
