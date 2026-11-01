//
// Created by ricka on 8/1/26.
//

#include "render_system.hpp"
#include "camera_2d_system.hpp"
#include "camera_3d_system.hpp"
#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/camera_3d.hpp>
#include <noi_engine/core/components/culling.hpp>
#include <noi_engine/core/components/fill_screen.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/mesh_renderer.hpp>
#include <noi_engine/core/components/render_layer.hpp>
#include <noi_engine/core/scene.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <cmath>
#include <stdexcept>
#include <algorithm>

#include "../glad/glad.h"

auto noi_engine::render_system::sorted_renderables(world& world) -> const std::vector<entity>&
{
    thread_local std::vector<entity> renderables;
    renderables.clear();

    for (const auto e : world.view<transform, world_matrix, mesh_renderer>())
        renderables.push_back(e);

    std::ranges::stable_sort(renderables, [&world](const entity lhs, const entity rhs)
                             -> bool
                             {
                                 const auto lhs_order = world.has<render_layer>(lhs)
                                                            ? world.get<render_layer>(lhs).order
                                                            : 0;
                                 const auto rhs_order = world.has<render_layer>(rhs)
                                                            ? world.get<render_layer>(rhs).order
                                                            : 0;
                                 return lhs_order < rhs_order;
                             });

    return renderables;
}


auto noi_engine::render_system::render(world& world, renderer& renderer, const entity& active_camera) -> void
{
    glm::mat4 view;
    glm::mat4 projection;

    if (world.has<camera_2d>(active_camera))
    {
        glDisable(GL_DEPTH_TEST);
        // After every update (scripts, physics) moved the camera this frame.
        apply_fill_screen(world, active_camera);
        view = camera_2d_system::view_matrix(world, active_camera);
        projection = camera_2d_system::projection_matrix(world, active_camera);
    }
    else if (world.has<camera_3d>(active_camera))
    {
        glEnable(GL_DEPTH_TEST);
        view = camera_3d_system::view_matrix(world, active_camera);
        projection = camera_3d_system::projection_matrix(world, active_camera);
    }
    else
    {
        throw std::runtime_error("active_camera has no camera_2d or camera_3d component");
    }

    // Culling (see culling.hpp): skip what lies outside the camera's view + margin. The
    // entity's quad spans its world matrix's x / y axes.
    view_area area;
    const bool culled = culling_area(world, active_camera, area);

    for (const auto e : sorted_renderables(world))
    {
        if (culled && !world.has<always_active>(e))
        {
            const auto& m = world.get<world_matrix>(e).value;
            const glm::vec2 half_size{
                (std::abs(m[0].x) + std::abs(m[1].x)) * 0.5f,
                (std::abs(m[0].y) + std::abs(m[1].y)) * 0.5f};
            if (!area.overlaps({m[3].x, m[3].y}, half_size))
            {
                continue;
            }
        }

        mesh_renderer_properties* properties = world.has<mesh_renderer_properties>(e)
                                                   ? &world.get<mesh_renderer_properties>(e)
                                                   : nullptr;

        renderer.draw(
            world.get<world_matrix>(e),
            world.get<mesh_renderer>(e),
            view,
            projection,
            properties);
    }
}

auto noi_engine::render_system::on_render(const script_context& ctx) -> void
{
    render(ctx.get_world(), *ctx.renderer, ctx.scene->get_camera_entity());
}
