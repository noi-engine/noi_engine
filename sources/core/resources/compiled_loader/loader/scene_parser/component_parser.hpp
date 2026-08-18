//
// Created by ricka on 8/16/26.
//

#pragma once

#include <noi_engine/core/resources/resources.hpp>

namespace noi_engine::c
{
    class i_component_parser
    {
    public:
        virtual ~i_component_parser() = default;

        virtual auto parse(const entity& entity, scene& target_scene, resources* resources,
                           const void* properties) -> void = 0;
    };

    class camera_2d_parser : public i_component_parser
    {
    public:
        auto parse(const entity& entity, scene& target_scene, resources* resources,
                   const void* properties)
            -> void override;
    };

    class script_component_parser final : public i_component_parser
    {
    public:
        auto parse(const entity& entity, scene& target_scene,
                   resources* resources, const void* properties)
            -> void override;
    };

    class transform_parser final : public i_component_parser
    {
    public:
        auto parse(const entity& entity, scene& target_scene,
                   resources* resources, const void* properties)
            -> void override;
    };

    class render_layer_parser final : public i_component_parser
    {
    public:
        auto parse(const entity& entity, scene& target_scene,
                   resources* resources, const void* properties)
            -> void override;
    };

    class mesh_renderer_parser final : public i_component_parser
    {
    public:
        auto parse(const entity& entity, scene& target_scene,
                   resources* resources, const void* properties)
            -> void override;
    };
} // namespace noi_engine
