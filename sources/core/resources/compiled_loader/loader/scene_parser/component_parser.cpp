//
// Created by ricka on 8/16/26.
//

#include "component_parser.hpp"
#include <glm/vec3.hpp>
#include "../fbs/scene_generated.h"
#include <noi_engine/core/model/script.hpp>
#include <noi_engine/core/components/dirty.hpp>
#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/render_layer.hpp>
#include <noi_engine/core/components/world_matrix.hpp>
#include <noi_engine/core/components/script_component.hpp>

namespace noi_engine::c
{
    auto camera_2d_parser::parse(const entity& entity, scene& target_scene,
                                 [[maybe_unused]] resources* resources,
                                 const void* properties) -> void
    {
        auto& world = target_scene.get_world();
        camera_2d value{};

        if (!properties)
        {
            world.add<camera_2d>(entity, value);
            return;
        }

        const auto camera_properties = static_cast<const fbs::Camera2DComponent*>(properties);

        if (camera_properties->zoom())
        {
            value.zoom = camera_properties->zoom();
        }

        if (camera_properties->near_plane())
        {
            value.near_plane = camera_properties->near_plane();
        }

        if (camera_properties->far_plane())
        {
            value.far_plane = camera_properties->far_plane();
        }

        if (camera_properties->orthographic_size())
        {
            value.orthographic_size = camera_properties->orthographic_size();
        }

        if (camera_properties->aspect_ratio_width() && camera_properties->aspect_ratio_height())
        {
            value.aspect_ratio = camera_properties->aspect_ratio_width() /
                camera_properties->aspect_ratio_height();
        }

        world.add<camera_2d>(entity, value);
    }

    auto script_component_parser::parse(const entity& entity,
                                        scene& target_scene,
                                        resources* resources,
                                        const void* properties) -> void
    {
        auto& world = target_scene.get_world();
        script_component value{};

        if (!properties)
        {
            return;
        }

        const auto scripts_properties = static_cast<const fbs::ScriptsComponent*>(properties);

        if (const auto* names = scripts_properties->names())
        {
            for (const auto* name : *names)
            {
                value.scripts.push_back(
                    resources->get_handle<script>(name->c_str())
                );
            }
        }

        world.add<script_component>(entity, value);
    }

    auto transform_parser::parse(const entity& entity,
                                 scene& target_scene,
                                 [[maybe_unused]] resources* resources,
                                 const void* properties) -> void
    {
        transform value{};

        if (!properties)
        {
            auto& world = target_scene.get_world();
            world.add(entity, value);
            world.add(entity, world_matrix{});
            world.add(entity, dirty<transform>{});
            return;
        }

        const auto transform_properties = static_cast<const fbs::TransformComponent*>(properties);

        if (const auto* position = transform_properties->position())
        {
            if (position->size() >= 3)
            {
                value.position = glm::vec3{
                    position->Get(0),
                    position->Get(1),
                    position->Get(2)
                };
            }
        }

        if (const auto* rotation = transform_properties->rotation())
        {
            if (rotation->size() >= 3)
            {
                value.rotation = glm::vec3{
                    rotation->Get(0),
                    rotation->Get(1),
                    rotation->Get(2)
                };
            }
        }

        if (const auto* scale = transform_properties->scale())
        {
            if (scale->size() >= 3)
            {
                value.scale = glm::vec3{
                    scale->Get(0),
                    scale->Get(1),
                    scale->Get(2)
                };
            }
        }

        auto& world = target_scene.get_world();
        world.add(entity, value);
        world.add(entity, world_matrix{});
        world.add(entity, dirty<transform>{});
    }

    auto render_layer_parser::parse(const entity& entity,
                                    scene& target_scene,
                                    [[maybe_unused]] resources* resources,
                                    const void* properties) -> void
    {
        render_layer value{};

        if (!properties)
        {
            target_scene.get_world().add(entity, value);
            return;
        }

        const auto render_layer_properties =
            static_cast<const fbs::RenderLayerComponent*>(properties);

        if (render_layer_properties->order())
        {
            value.order = render_layer_properties->order();
        }

        target_scene.get_world().add(entity, value);
    }

    auto mesh_renderer_parser::parse(const entity& entity,
                                     scene& target_scene,
                                     resources* resources,
                                     const void* properties) -> void
    {
        mesh_renderer value{};

        if (!properties)
        {
            target_scene.get_world().add(entity, value);
            return;
        }

        const auto mesh_renderer_properties =
            static_cast<const fbs::MeshRendererComponent*>(properties);

        if (mesh_renderer_properties->mesh())
        {
            value.m_mesh = resources->get_handle<mesh>(
                mesh_renderer_properties->mesh()->str()
            );
        }

        if (mesh_renderer_properties->material())
        {
            value.m_material = resources->get_handle<material>(
                mesh_renderer_properties->material()->str()
            );
        }

        target_scene.get_world().add<mesh_renderer>(entity, value);
    }
}
