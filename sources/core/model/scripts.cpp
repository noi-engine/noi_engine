//
// Created by ricka on 8/9/26.
//

#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/model/script.hpp>

auto noi_engine::details::script_registry::instance() -> script_registry&
{
    static script_registry registry;
    return registry;
}

auto noi_engine::script_context::get_world() const -> world&
{
    return this->scene->get_world();
}

auto noi_engine::script::on_create([[maybe_unused]] const entity self,
                                   [[maybe_unused]] const script_context& ctx)
    -> void
{
}

auto noi_engine::script::on_before_update(
    [[maybe_unused]] const entity self,
    [[maybe_unused]] const script_context& ctx, [[maybe_unused]] float dt)
    -> void
{
}

auto noi_engine::script::on_update([[maybe_unused]] const entity self,
                                   [[maybe_unused]] const script_context& ctx,
                                   [[maybe_unused]] float dt) -> void
{
}

auto noi_engine::script::on_after_update(
    [[maybe_unused]] const entity self,
    [[maybe_unused]] const script_context& ctx, [[maybe_unused]] float dt)
    -> void
{
}

auto noi_engine::script::on_before_render(
    [[maybe_unused]] const entity self,
    [[maybe_unused]] const script_context& ctx) -> void
{
}

auto noi_engine::script::on_after_render(
    [[maybe_unused]] const entity self,
    [[maybe_unused]] const script_context& ctx) -> void
{
}

auto noi_engine::script::on_destroy([[maybe_unused]] const entity self,
                                    [[maybe_unused]] const script_context& ctx)
    -> void
{
}

auto noi_engine::script::add_dirty_transform(const entity self, const script_context& ctx) -> void
{
    ctx.get_world().add_dirty_transform(self);
}

auto noi_engine::script::add_transform(const entity self, const script_context& ctx, const transform& value) -> void
{
    ctx.get_world().add_transform(self, value);
}
