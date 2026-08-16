//
// Created by ricka on 8/16/26.
//

#include "component_parser.hpp"

#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/script_component.hpp>
#include <noi_engine/core/scripts/script.hpp>

namespace noi_engine
{
    auto camera_2d_parser::parse(const entity& entity, scene& target_scene,
                                 resource_system* resources,
                                 const nlohmann::json& properties) -> void
    {
        const float zoom = properties.value("zoom", 1.0f);
        const float near_plane = properties.value("near_plane", -1.0f);
        const float far_plane = properties.value("far_plane", 1.0f);
        const float ortho_size = properties.value("orthographic_size", 5.0f);
        const float aspect_ratio_width = properties.value("aspect_ratio_width", 16);
        const float aspect_ratio_height = properties.value("aspect_ratio_width", 9);

        auto& world = target_scene.get_world();
        world.add<camera_2d>(entity, camera_2d{
                                 .zoom = zoom,
                                 .near_plane = near_plane,
                                 .far_plane = far_plane,
                                 .aspect_ratio = aspect_ratio_width / aspect_ratio_height,
                                 .orthographic_size = ortho_size,
                             });
    }

    auto script_component_parser::parse(const entity& entity,
                                        scene& target_scene,
                                        resource_system* resources,
                                        const nlohmann::json& properties) -> void
    {
        if (!properties.contains("names") || !resources)
        {
            return;
        }

        std::vector<resource_handle<script>> scripts{};
        for (const auto& script_name : properties["names"])
        {
            auto script_handle = resources->get_handle<script>(script_name.get<std::string>());
            scripts.push_back(script_handle);
        }

        target_scene.get_world().add<script_component>(entity, script_component{.scripts = scripts});
    }
}
