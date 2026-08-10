//
// Created by ricka on 8/9/26.
//

#pragma once

#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/scripts/script.hpp>
#include <noi_engine/core/resources/resource_handle.hpp>
#include <noi_engine/core/model/shader.hpp>
#include <noi_engine/core/model/mesh.hpp>
#include <noi_engine/core/resources/resource_system.hpp>

namespace sandbox::basic
{
    class player_script : public noi_engine::script
    {
        noi_engine::resource_system* m_resources{nullptr};
        noi_engine::resource_handle<noi_engine::mesh> m_quad_mesh;
        noi_engine::resource_handle<noi_engine::shader> m_color_shader;

    public:
        auto on_create() -> void override;
        auto on_update(float dt) -> void override;

        explicit player_script(
            noi_engine::resource_system *resources,
            noi_engine::resource_handle<noi_engine::mesh> mesh,
            noi_engine::resource_handle<noi_engine::shader> color_shader);
    };

    class camera_script : public noi_engine::script
    {
        noi_engine::entity m_player;

    public:
        auto on_create() -> void override;

        explicit camera_script(noi_engine::entity player);
    };

    class background_script : public noi_engine::script
    {
        noi_engine::resource_system* m_resources{nullptr};
        noi_engine::resource_handle<noi_engine::mesh> m_quad_mesh;
        noi_engine::resource_handle<noi_engine::shader> m_color_shader;

    public:
        auto on_create() -> void override;

        explicit background_script(
            noi_engine::resource_system *resources,
            noi_engine::resource_handle<noi_engine::mesh> mesh,
            noi_engine::resource_handle<noi_engine::shader> color_shader);
    };
}
