//
// Created by ricka on 8/2/26.
//

#include <noi_engine/core/systems/camera_2d_system.hpp>
#include <noi_engine/core/components/camera_2d.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <algorithm>

auto noi_engine::camera_2d_system::update(world& world, const entity camera_entity, const input_state& input) -> void
{
    auto& cam = world.get<camera_2d>(camera_entity);

    if (input.is_mouse_button_down(SDL_BUTTON_MIDDLE))
    {
        const auto delta = input.get_mouse_delta();
        cam.position.x -= delta.x * cam.pan_sensitivity / cam.zoom;
        cam.position.y += delta.y * cam.pan_sensitivity / cam.zoom;
    }

    cam.zoom += input.get_scroll_delta() * cam.zoom_speed * cam.zoom;
    cam.zoom = std::clamp(cam.zoom, cam.min_zoom, cam.max_zoom);
}

auto noi_engine::camera_2d_system::view_matrix(world& world, const entity camera_entity) -> glm::mat4
{
    const auto& cam = world.get<camera_2d>(camera_entity);

    auto view = glm::mat4{1.0f};
    view = glm::scale(view, glm::vec3{cam.zoom, cam.zoom, 1.0f});
    view = glm::translate(view, glm::vec3{-cam.position.x, -cam.position.y, 0.0f});
    return view;
}

auto noi_engine::camera_2d_system::projection_matrix(world& world, const entity camera_entity) -> glm::mat4
{
    const auto& cam = world.get<camera_2d>(camera_entity);

    const auto half_height = cam.orthographic_size;
    const auto half_width = half_height * cam.aspect_ratio;

    return glm::ortho(-half_width, half_width, -half_height, half_height, cam.near_plane, cam.far_plane);
}
