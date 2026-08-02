//
// Created by ricka on 8/1/26.
//

#include <noi_engine/core/systems/render_system.hpp>
#include <noi_engine/core/systems/orbit_camera_system.hpp>
#include <noi_engine/core/systems/camera_2d_system.hpp>
#include <noi_engine/core/systems/camera_3d_system.hpp>
#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/camera_3d.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/mesh_renderer.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <stdexcept>

auto noi_engine::render_system::render(world& world, renderer& renderer, const entity& active_camera) -> void
{
    glm::mat4 view;
    glm::mat4 projection;

    if (world.pool<camera_2d>().has(active_camera))
    {
        view = camera_2d_system::view_matrix(world, active_camera);
        projection = camera_2d_system::projection_matrix(world, active_camera);
    }
    else if (world.pool<camera_3d>().has(active_camera))
    {
        view = camera_3d_system::view_matrix(world, active_camera);
        projection = camera_3d_system::projection_matrix(world, active_camera);
    }
    else
    {
        throw std::runtime_error("active_camera has no camera_2d or camera_3d component");
    }

    for (const auto entity : world.view<transform, mesh_renderer>())
    {
        renderer.draw(world.get<transform>(entity), world.get<mesh_renderer>(entity), view, projection);
    }
}