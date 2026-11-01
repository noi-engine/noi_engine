//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/camera_3d.hpp>
#include <noi_engine/core/components/dirty.hpp>
#include <noi_engine/core/components/world_matrix.hpp>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/model/script.hpp>
#include <utility>

#include "systems/camera_system.hpp"
#include "systems/render_system.hpp"
#include "systems/script_runner_system.hpp"
#include "systems/transform_system.hpp"

static auto to_base_script_context(const noi_engine::scene_context& context,
                                   noi_engine::scene* scene)
    -> noi_engine::script_context
{
    return {
        .game = context.game,
        .scene = scene,
        .input = context.input,
        .renderer = context.renderer,
        .resources = context.resources
    };
}

auto noi_engine::scene::get_aspect_ratio() -> float
{
    if (m_world.has<camera_2d>(m_camera_entity))
    {
        const auto& cam = m_world.get<camera_2d>(m_camera_entity);
        return cam.aspect_ratio;
    }
    if (m_world.has<camera_3d>(m_camera_entity))
    {
        const auto& cam = m_world.get<camera_3d>(m_camera_entity);
        return cam.aspect_ratio;
    }

    return 0;
}

noi_engine::scene::scene(std::string name) : m_name(std::move(name))
{
    this->m_camera_entity = m_world.create_entity();
    m_world.add_transform(m_camera_entity, transform{});

    // Minimal default pipeline every scene needs to run scripts, place, aim, and draw its
    // entities. Optional builtins (physics, orbit camera, ...) are opt-in via add_system<T>().
    add_system<script_runner_system>();
    add_system<transform_system>();
    add_system<camera_system>();
    add_system<render_system>();
}

auto noi_engine::scene::update(const scene_context& context, const float dt)
    -> void
{
    const auto ctx = to_base_script_context(context, this);

    for (const auto& slot : m_systems)
        slot.instance->on_before_update(ctx, dt);

    for (const auto& slot : m_systems)
        slot.instance->on_update(ctx, dt);

    for (const auto& slot : m_systems)
        slot.instance->on_after_update(ctx, dt);

    m_world.signals().dispatch(dt);
}

auto noi_engine::scene::render(const scene_context& context) -> void
{
    const auto ctx = to_base_script_context(context, this);

    for (const auto& slot : m_systems)
        slot.instance->on_before_render(ctx);

    for (const auto& slot : m_systems)
        slot.instance->on_render(ctx);

    for (const auto& slot : m_systems)
        slot.instance->on_after_render(ctx);
}

auto noi_engine::scene::find_system_slot(const std::type_index type)
    -> std::vector<system_slot>::iterator
{
    return std::find_if(m_systems.begin(), m_systems.end(),
                        [type](const system_slot& slot) { return slot.type == type; });
}

auto noi_engine::scene::resort_systems() -> void
{
    std::stable_sort(m_systems.begin(), m_systems.end(),
                     [](const system_slot& lhs, const system_slot& rhs)
                     {
                         return lhs.priority < rhs.priority;
                     });
}

auto noi_engine::scene::systems() const -> std::vector<std::pair<std::string_view, int>>
{
    std::vector<std::pair<std::string_view, int>> result;
    result.reserve(m_systems.size());

    for (const auto& slot : m_systems)
        result.emplace_back(slot.instance->name(), slot.priority);

    return result;
}

auto noi_engine::scene::on_enter([[maybe_unused]] const scene_context& context)
    -> void
{
}

auto noi_engine::scene::on_exit([[maybe_unused]] const scene_context& context)
    -> void
{
}

auto noi_engine::scene::on_resize([[maybe_unused]] const scene_context& context,
                                  [[maybe_unused]] const int width, [[maybe_unused]] const int height) -> void
{
}

auto noi_engine::scene::get_world() -> world&
{
    return this->m_world;
}

auto noi_engine::scene::get_camera_entity() const -> entity
{
    return this->m_camera_entity;
}

auto noi_engine::scene::set_scripts_paused(const bool paused) -> void
{
    this->m_scripts_paused = paused;
}

auto noi_engine::scene::scripts_paused() const -> bool
{
    return this->m_scripts_paused;
}
