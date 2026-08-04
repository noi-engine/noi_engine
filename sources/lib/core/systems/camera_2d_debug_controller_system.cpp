//
// Created by ricka on 8/2/26.
//

#include "camera_2d_debug_controller_system.hpp"
#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/camera_2d_debug_controller.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/dirty.hpp>
#include <SDL2/SDL_mouse.h>
#include <algorithm>

auto noi_engine::camera_2d_debug_controller_system::update(world& world, const entity camera_entity,
                                                           const input_state& input) -> void
{
    auto& cam = world.get<camera_2d>(camera_entity);
    const auto& ctrl = world.get<camera_2d_debug_controller>(camera_entity);

    if (input.is_mouse_button_down(SDL_BUTTON_MIDDLE))
    {
        const auto delta = input.get_mouse_delta();
        auto& tr = world.get<transform>(camera_entity);

        tr.position.x -= delta.x * ctrl.pan_sensitivity / cam.zoom;
        tr.position.y += delta.y * ctrl.pan_sensitivity / cam.zoom;

        world.add(camera_entity, dirty<transform>{});
    }

    cam.zoom += input.get_scroll_delta() * ctrl.zoom_speed * cam.zoom;
    cam.zoom = std::clamp(cam.zoom, ctrl.min_zoom, ctrl.max_zoom);
}
