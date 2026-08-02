//
// Created by ricka on 8/2/26.
//

#include <noi_engine/core/systems/camera_3d_system.hpp>
#include <noi_engine/core/components/camera_3d.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/orbit_camera.hpp>
#include <noi_engine/core/systems/orbit_camera_system.hpp>
#include <noi_engine/core/components/world_matrix.hpp>
#include <glm/ext/matrix_clip_space.hpp>


auto noi_engine::camera_3d_system::view_matrix(world& world, const entity camera_entity) -> glm::mat4
{
    if (world.has<orbit_camera>(camera_entity))
    {
        return orbit_camera_system::view_matrix(world, camera_entity);
    }

    const auto world_matrix = world.get<noi_engine::world_matrix>(camera_entity);
    return glm::inverse(world_matrix.value);
}

auto noi_engine::camera_3d_system::projection_matrix(world& world, const entity camera_entity) -> glm::mat4
{
    const auto& cam = world.get<camera_3d>(camera_entity);
    return glm::perspective(glm::radians(cam.fov), cam.aspect_ratio, cam.near_plane, cam.far_plane);
}

auto noi_engine::camera_3d_system::update(world& world, const entity camera_entity, const input_state& input) -> void
{
    orbit_camera_system::update(world, camera_entity, input);
}
