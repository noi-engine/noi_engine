//
// Created by ricka on 8/1/26.
//

#include <noi_engine/core/systems/orbit_camera_system.hpp>
#include <noi_engine/core/components/orbit_camera.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <algorithm>
#include <cmath>

auto noi_engine::orbit_camera_system::update(world& world, const entity camera_entity, const input_state& input) -> void
{
    auto& cam = world.get<orbit_camera>(camera_entity);

    if (input.left_mouse_held)
    {
        cam.yaw -= input.mouse_delta_x * cam.sensitivity * 0.01f;
        cam.pitch -= input.mouse_delta_y * cam.sensitivity * 0.01f;
        cam.pitch = std::clamp(cam.pitch, cam.min_pitch, cam.max_pitch);
    }

    cam.distance -= input.scroll_delta * cam.zoom_speed;
    cam.distance = std::clamp(cam.distance, cam.min_distance, cam.max_distance);
}

auto noi_engine::orbit_camera_system::view_matrix(world& world, const entity camera_entity) -> glm::mat4
{
    const auto& cam = world.get<orbit_camera>(camera_entity);

    const auto position = cam.target + glm::vec3{
        cam.distance * std::cos(cam.pitch) * std::sin(cam.yaw),
        cam.distance * std::sin(cam.pitch),
        cam.distance * std::cos(cam.pitch) * std::cos(cam.yaw)
    };

    return glm::lookAt(position, cam.target, glm::vec3{0.0f, 1.0f, 0.0f});
}
