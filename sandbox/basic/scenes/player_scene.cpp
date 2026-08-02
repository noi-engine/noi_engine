//
// Created by ricka on 8/2/26.
//

#include "player_scene.hpp"

#include <noi_engine/core/components/camera_2d.hpp>

#include "../systems/movement_system.hpp"
#include "../systems/player_controller_system.hpp"

sandbox::basic::player_scene::player_scene() : scene("player_scene")
{
    m_world.add<noi_engine::camera_2d>(m_camera_entity, noi_engine::camera_2d{
                                           .orthographic_size = 5.0f
                                       });
}

auto sandbox::basic::player_scene::update(const float dt, const noi_engine::input_state& input) -> void
{
    player_controller_system::update(m_world, input);
    movement_system::update(m_world, dt);

    scene::update(dt, input);
}
