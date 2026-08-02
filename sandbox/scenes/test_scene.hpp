//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/components/camera_3d.hpp>
#include <noi_engine/core/components/orbit_camera.hpp>

class test_scene : public noi_engine::scene
{
public:
    test_scene() : scene("test_scene")
    {
        m_world.add<noi_engine::camera_3d>(m_camera_entity, noi_engine::camera_3d{});;
        m_world.add(m_camera_entity, noi_engine::orbit_camera{
                        .target = {0.0f, 0.0f, 0.0f},
                        .distance = 5.0f
                    });
    }
};
