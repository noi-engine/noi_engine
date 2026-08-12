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

auto noi_engine::script::attach(const script_context& context) noexcept -> void
{
    m_context.self = context.self;
    m_context.input = context.input;
    m_context.scene = context.scene;
    m_context.world = context.world;
}

auto noi_engine::script::get_scene() const -> scene*
{
    return m_context.scene;
}

auto noi_engine::script::get_input() const -> input_state*
{
    return m_context.input;
}

auto noi_engine::script::get_world() const -> world*
{
    return m_context.world;
}

auto noi_engine::script::get_self() const noexcept -> entity
{
    return m_context.self;
}
