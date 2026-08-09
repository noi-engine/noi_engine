//
// Created by ricka on 8/9/26.
//

#pragma once

#include <utility>
#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/ecs/world.hpp>

namespace noi_engine
{
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

        auto attach(world& world, entity self) noexcept -> void;

    protected:
        [[nodiscard]] auto get_world() const -> world*;
        [[nodiscard]] auto get_self() const noexcept -> entity;

        template <typename T>
        [[nodiscard]] auto get() -> T
        {
            return m_world->get<T>(get_self());
        }

        template <typename T>
        auto add(T value) const -> void
        {
            m_world->add<T>(m_self, value);
        }

        template <typename T>
        [[nodiscard]] auto has() const -> bool
        {
            return m_world->has<T>(get_self());
        }

        template <typename Signal>
            requires is_signal<Signal>
        auto emit(Signal signal) -> void
        {
            signal.source = m_self;
            m_world->signals().emit<Signal>(std::move(signal));
        }

        template <typename Signal>
            requires is_signal<Signal>
        auto connect(const entity source, std::function<void(float dt, const Signal&)> callback)
        {
            return m_world->signals().connect<Signal>(source, std::move(callback));
        }

        template <typename Signal>
            requires is_signal<Signal>
        auto connect(std::function<void(const float dt, const Signal&)> callback)
        {
            return m_world->signals().connect<Signal>(std::move(callback));
        }

    private:
        world* m_world{nullptr};
        entity m_self{};
    };
}
