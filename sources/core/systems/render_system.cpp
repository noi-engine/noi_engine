//
// Created by ricka on 8/1/26.
//

#include <glm/ext/matrix_clip_space.hpp>
#include <noi_engine/core/systems/render_system.hpp>
#include <noi_engine/core/components/camera.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/mesh_renderer.hpp>

auto noi_engine::render_system::render(world& world, renderer& renderer, const entity& active_camera) -> void
{
    const auto& camera = world.get<noi_engine::camera>(active_camera);
    const auto& camera_transform = world.get<noi_engine::transform>(active_camera);

    auto view = glm::inverse(camera_transform.model());
    auto projection = glm::perspective(
        glm::radians(camera.fov),
        camera.aspect_ratio,
        camera.near_plane,
        camera.far_plane
    );

    for (const auto entity : world.view<transform, mesh_renderer>())
    {
        auto& transform = world.get<noi_engine::transform>(entity);
        auto& mesh_renderer = world.get<noi_engine::mesh_renderer>(entity);

        renderer.draw(
            transform,
            mesh_renderer,
            view,
            projection
        );
    }
}
