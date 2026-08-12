//
// Created by ricka on 8/9/26.
//

#include "script_system.hpp"
#include <noi_engine/core/components/script_component.hpp>

namespace
{
    auto ensure_created(const noi_engine::script_context& context) -> void
    {
        for (const auto e : context.world->view<noi_engine::script_component>())
        {
            auto& comp = context.world->get<noi_engine::script_component>(e);

            if (!comp.instance || comp.created)
            {
                continue;
            }

            comp.instance->attach({
                .self = e,
                .world = context.world,
                .scene = context.scene,
                .input = context.input
            });

            comp.instance->on_create();
            comp.created = true;
        }
    }
}

auto noi_engine::script_system::before_update(const script_context& context, const float dt) -> void
{
    ensure_created(context);

    for (const auto e : context.world->view<script_component>())
    {
        if (const auto& comp = context.world->get<script_component>(e); comp.instance)
        {
            comp.instance->on_before_update(dt);
        }
    }
}

auto noi_engine::script_system::update(world& world, const float dt) -> void
{
    for (const auto e : world.view<script_component>())
    {
        if (const auto& comp = world.get<script_component>(e); comp.instance)
        {
            comp.instance->on_update(dt);
        }
    }
}

auto noi_engine::script_system::after_update(world& world, const float dt) -> void
{
    for (const auto e : world.view<script_component>())
    {
        if (const auto& comp = world.get<script_component>(e); comp.instance)
        {
            comp.instance->on_after_update(dt);
        }
    }
}

auto noi_engine::script_system::before_render(world& world) -> void
{
    for (const auto e : world.view<script_component>())
    {
        if (const auto& comp = world.get<script_component>(e); comp.instance)
        {
            comp.instance->on_before_render();
        }
    }
}

auto noi_engine::script_system::after_render(world& world) -> void
{
    for (const auto e : world.view<script_component>())
    {
        if (const auto& comp = world.get<script_component>(e); comp.instance)
        {
            comp.instance->on_after_render();
        }
    }
}

auto noi_engine::script_system::destroy(world& world, const entity target) -> void
{
    if (!world.has<script_component>(target))
    {
        return;
    }

    if (const auto& comp = world.get<script_component>(target); comp.instance && comp.created)
    {
        comp.instance->on_destroy();
    }
}
