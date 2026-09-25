//
// Created by ricka on 8/2/26.
//

#include "camera_3d_system.hpp"
#include <noi_engine/builtin/components/orbit_camera.hpp>
#include <noi_engine/builtin/systems/orbit_camera_system.hpp>
#include <noi_engine/core/components/camera_3d.hpp>
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

auto noi_engine::camera_3d_system::update([[maybe_unused]] world& world, [[maybe_unused]] const entity camera_entity,
                                          [[maybe_unused]] const input_state& input) -> void
{
    // Camera movement is driven by the transform (scripts, orbit_camera_system if opted into, ...);
    // this system only ever reads it back for view_matrix(). Kept for symmetry with camera_2d_system.
}
