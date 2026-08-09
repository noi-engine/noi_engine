//
// Created by ricka on 8/9/26.
//

#pragma once

#include <utility>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/input/input_state.hpp>

namespace noi_engine
{
    struct script_context
    {
        entity self{};
        world* world{nullptr};
        scene* scene{nullptr};
        input_state* input{nullptr};
    };

    class script
    {
    public:
        virtual ~script() = default;

        virtual auto on_create() -> void;
        virtual auto on_before_update(float dt) -> void;
        virtual auto on_update(float dt) -> void;
        virtual auto on_after_update(float dt) -> void;
        virtual auto on_before_render() -> void;
        virtual auto on_after_render() -> void;
        virtual auto on_destroy() -> void;

        auto attach(const script_context& script_context) noexcept -> void;

    protected:
        [[nodiscard]] auto get_scene() const -> scene*;
        [[nodiscard]] auto get_world() const -> world*;
        [[nodiscard]] auto get_input() const -> input_state*;
        [[nodiscard]] auto get_self() const noexcept -> entity;

        template <typename T>
        [[nodiscard]] auto get() -> T
        {
            return get_world()->get<T>(get_self());
        }

        template <typename T>
        auto add(T value) const -> void
        {
            get_world()->add<T>(get_self(), value);
        }

        template <typename T>
        [[nodiscard]] auto has() const -> bool
        {
            return get_world()->has<T>(get_self());
        }

        template <typename Signal>
            requires details::is_signal<Signal>
        auto emit(Signal signal) -> void
        {
            signal.source = get_self();
            get_world()->signals().emit<Signal>(std::move(signal));
        }

        template <typename Signal>
            requires details::is_signal<Signal>
        auto connect(const entity source, std::function<void(float dt, const Signal&)> callback)
        {
            return get_world()->signals().connect<Signal>(source, std::move(callback));
        }

        template <typename Signal>
            requires details::is_signal<Signal>
        auto connect(std::function<void(float dt, const Signal&)> callback)
        {
            return get_world()->signals().connect<Signal>(std::move(callback));
        }

    private:
        script_context m_context{};
    };
}
