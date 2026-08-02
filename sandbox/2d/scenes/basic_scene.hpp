//
// Created by ricka on 8/2/26.
//

#pragma once

#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/camera_2d_debug_controller.hpp>

namespace sandbox::twod::scenes
{
    class basic_scene : public noi_engine::scene
    {
    public:
        basic_scene() : scene("basic_scene")
        {
            m_world.add<noi_engine::camera_2d>(m_camera_entity, noi_engine::camera_2d{
                                                   .orthographic_size = 5.0f
                                               });
            m_world.add(m_camera_entity, noi_engine::camera_2d_debug_controller{});
        }
    };
}
