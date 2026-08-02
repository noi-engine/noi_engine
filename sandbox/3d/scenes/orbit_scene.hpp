//
// Created by ricka on 8/2/26.
//

#pragma once

#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/components/camera_3d.hpp>
#include <noi_engine/core/components/orbit_camera.hpp>

namespace sandbox::scenes
{
    class orbit_scene : public noi_engine::scene
    {
    public:
        orbit_scene() : scene("orbit_scene")
        {
            m_world.add<noi_engine::camera_3d>(m_camera_entity, noi_engine::camera_3d{});;
            m_world.add(m_camera_entity, noi_engine::orbit_camera{
                            .target = {0.0f, 0.0f, 0.0f},
                            .distance = 5.0f
                        });
        }
    };
}
