//
// Created by ricka on 8/1/26.
//

#include <noi_engine/core/systems/render_system.hpp>
#include <noi_engine/core/systems/orbit_camera_system.hpp>
#include <noi_engine/core/components/orbit_camera.hpp>
#include <noi_engine/core/components/camera.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/mesh_renderer.hpp>
#include <glm/ext/matrix_clip_space.hpp>

auto noi_engine::render_system::render(world& world, renderer& renderer, const entity& active_camera) -> void
{
    const auto& camera = world.get<noi_engine::camera>(active_camera);

    const auto view = world.pool<orbit_camera>().has(active_camera)
                          ? orbit_camera_system::view_matrix(world, active_camera)
                          : glm::inverse(world.get<transform>(active_camera).model());

    const auto projection = glm::perspective(
        glm::radians(camera.fov),
        camera.aspect_ratio,
        camera.near_plane,
        camera.far_plane
    );

    for (const auto entity : world.view<transform, mesh_renderer>())
    {
        const auto& t = world.get<transform>(entity);
        const auto& mr = world.get<mesh_renderer>(entity);

        renderer.draw(t, mr, view, projection);
    }
}
