//
// Created by ricka on 8/1/26.
//

#include <noi_engine/core/systems/render_system.hpp>
#include <noi_engine/core/systems/orbit_camera_system.hpp>
#include <noi_engine/core/systems/camera_2d_system.hpp>
#include <noi_engine/core/components/orbit_camera.hpp>
#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/camera.hpp>
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
    else if (world.pool<camera>().has(active_camera))
    {
        const auto& cam = world.get<camera>(active_camera);

        view = world.pool<orbit_camera>().has(active_camera)
                   ? orbit_camera_system::view_matrix(world, active_camera)
                   : glm::inverse(world.get<transform>(active_camera).model());

        projection = glm::perspective(glm::radians(cam.fov), cam.aspect_ratio, cam.near_plane, cam.far_plane);
    }
    else
    {
        throw std::runtime_error("active_camera has no camera or camera_2d component");
    }

    for (const auto entity : world.view<transform, mesh_renderer>())
    {
        const auto& t = world.get<transform>(entity);
        const auto& mr = world.get<mesh_renderer>(entity);

        renderer.draw(t, mr, view, projection);
    }
}
