//
// Created by ricka on 8/2/26.
//

#pragma once

#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/model/mesh.hpp>
#include <noi_engine/core/model/shader.hpp>

namespace sandbox::basic
{
    class player_scene : public noi_engine::scene
    {
        noi_engine::resource_handle<noi_engine::shader> m_color_shader;
        noi_engine::resource_handle<noi_engine::mesh> m_quad_mesh;

    public:
        player_scene();

        auto update(float dt, noi_engine::input_state& input) -> void override;

        auto on_enter(noi_engine::resource_system* resources) -> void override;
    };
}
