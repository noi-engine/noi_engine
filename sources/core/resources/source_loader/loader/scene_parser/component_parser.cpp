//
// Created by ricka on 8/16/26.
//

#include "component_parser.hpp"

#include <glm/vec3.hpp>
#include <noi_engine/core/model/script.hpp>
#include <noi_engine/core/components/dirty.hpp>
#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/render_layer.hpp>
#include <noi_engine/core/components/world_matrix.hpp>
#include <noi_engine/core/components/script_component.hpp>

namespace noi_engine
{
    auto camera_2d_parser::parse(
      const entity& entity,
      scene& target_scene,
      [[maybe_unused]] resources* resources,
      const nlohmann::json& properties) -> void
    {
        camera_2d camera{};

        if (properties.contains("zoom"))
        {
            camera.zoom = properties["zoom"].get<float>();
        }

        if (properties.contains("near_plane"))
        {
            camera.near_plane = properties["near_plane"].get<float>();
        }

        if (properties.contains("far_plane"))
        {
            camera.far_plane = properties["far_plane"].get<float>();
        }

        if (properties.contains("orthographic_size"))
        {
            camera.orthographic_size = properties["orthographic_size"].get<float>();
        }

        if (properties.contains("aspect_ratio_width") &&
            properties.contains("aspect_ratio_height"))
        {
            const auto width = properties["aspect_ratio_width"].get<float>();
            const auto height = properties["aspect_ratio_height"].get<float>();

            camera.aspect_ratio = width / height;
        }

        auto& world = target_scene.get_world();

        world.add<camera_2d>(entity, camera);
    }

    auto script_component_parser::parse(const entity& entity,
                                        scene& target_scene,
                                        resources* resources,
                                        const nlohmann::json& properties) -> void
    {
        std::vector<resource_handle<script>> scripts{};
        for (const auto& script_name : properties["names"])
        {
            auto script_handle = resources->get_handle<script>(script_name.get<std::string>());
            scripts.push_back(script_handle);
        }

        target_scene.get_world().add<script_component>(entity, script_component{.scripts = scripts});
    }

    auto transform_parser::parse(const entity& entity, scene& target_scene, [[maybe_unused]] resources* resources,
                                 const nlohmann::json& properties) -> void
    {
        transform value{};

        if (properties.contains("position"))
        {
            const auto position = properties["position"];
            const float x = position[0];
            const float y = position[1];
            const float z = position[2];
            value.position = glm::vec3(x, y, z);
        };

        if (properties.contains("rotation"))
        {
            const auto rotation = properties["rotation"];
            const float x = rotation[0];
            const float y = rotation[1];
            const float z = rotation[2];
            value.rotation = glm::vec3(x, y, z);
        };

        if (properties.contains("scale"))
        {
            const auto scale = properties["scale"];
            const float x = scale[0];
            const float y = scale[1];
            const float z = scale[2];
            value.scale = glm::vec3(x, y, z);
        };

        auto& world = target_scene.get_world();
        world.add(entity, value);
        world.add(entity, world_matrix{});
        world.add(entity, dirty<transform>{});
    }

    auto render_layer_parser::parse(const entity& entity, scene& target_scene, [[maybe_unused]] resources* resources,
                                    const nlohmann::json& properties) -> void
    {
        const int order = properties.value("order", 0);
        target_scene.get_world().add(entity, render_layer{.order = order});
    }

    auto mesh_renderer_parser::parse(const entity& entity, scene& target_scene, resources* resources,
                                     const nlohmann::json& properties) -> void
    {
        const auto mesh_value = resources->get_handle<mesh>(properties["mesh"].get<std::string>());
        const auto material_value = resources->get_handle<material>(properties["material"].get<std::string>());
        target_scene.get_world().add<mesh_renderer>(entity, mesh_renderer{
                                                        .m_mesh = mesh_value,
                                                        .m_material = material_value,
                                                    });
    }
}
