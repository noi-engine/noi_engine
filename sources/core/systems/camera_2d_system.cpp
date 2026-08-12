//
// Created by ricka on 8/2/26.
//

#include "camera_2d_system.hpp"
#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

auto noi_engine::camera_2d_system::update([[maybe_unused]] world& world, [[maybe_unused]] const entity camera_entity,
                                          [[maybe_unused]] const input_state& input) -> void
{
}

auto noi_engine::camera_2d_system::view_matrix(world& world, const entity camera_entity) -> glm::mat4
{
    const auto& cam = world.get<camera_2d>(camera_entity);
    const auto& tr = world.get<transform>(camera_entity);

    auto view = glm::mat4{1.0f};
    view = glm::scale(view, glm::vec3{cam.zoom, cam.zoom, 1.0f});
    view = glm::translate(view, glm::vec3{-tr.position.x, -tr.position.y, 0.0f});
    return view;
}

auto noi_engine::camera_2d_system::projection_matrix(world& world, const entity camera_entity) -> glm::mat4
{
    const auto& cam = world.get<camera_2d>(camera_entity);

    const auto half_height = cam.orthographic_size;
    const auto half_width = half_height * cam.aspect_ratio;

    return glm::ortho(-half_width, half_width, -half_height, half_height, cam.near_plane, cam.far_plane);
}
