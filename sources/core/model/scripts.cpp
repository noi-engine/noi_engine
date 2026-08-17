//
// Created by ricka on 8/9/26.
//

#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/model/script.hpp>

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
