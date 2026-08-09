//
// Created by ricka on 8/9/26.
//

#include <noi_engine/core/scripts/script.hpp>

auto noi_engine::script::on_create() -> void
{
}

auto noi_engine::script::on_before_update([[maybe_unused]] float dt) -> void
{
}

auto noi_engine::script::on_update([[maybe_unused]] float dt) -> void
{
}

auto noi_engine::script::on_after_update([[maybe_unused]] float dt) -> void
{
}

auto noi_engine::script::on_before_render() -> void
{
}

auto noi_engine::script::on_after_render() -> void
{
}

auto noi_engine::script::on_destroy() -> void
{
}

auto noi_engine::script::attach(world& world, const entity self) noexcept -> void
{
    m_world = &world;
    m_self = self;
}

auto noi_engine::script::get_world() const -> world*
{
    return m_world;
}

auto noi_engine::script::get_self() const noexcept -> entity
{
    return m_self;
}
