//
// Created by ricka on 8/16/26.
//

#include "box_collider_parser.hpp"
#include "culling_parser.hpp"
#include "color_parser.hpp"
#include "scene_parser.hpp"
#include "component_parser.hpp"
#include <noi_engine/core/components/name_component.hpp>

noi_engine::scene_parser::scene_parser(resources* resources) : m_resources(resources)
{
}

auto noi_engine::scene_parser::parse(const nlohmann::json& root_json) const -> std::unique_ptr<scene>
{
    auto loaded_scene = std::make_unique<scene>(root_json.value("name", "Untitled Scene"));

    if (root_json.contains("resources"))
    {
        parse_resources(root_json["resources"]);
    }

    if (root_json.contains("entities"))
    {
        parse_entities(*loaded_scene, root_json["entities"]);
    }

    return loaded_scene;
}

auto noi_engine::scene_parser::parse_resources(const nlohmann::json& res_json) const -> void
{
    if (res_json.contains("shaders"))
    {
        for (const auto& item : res_json["shaders"])
        {
            m_resources->load_from_path<shader>(item["name"].get<std::string>(), item["path"].get<std::string>());
        }
    }

    if (res_json.contains("textures"))
    {
        for (const auto& item : res_json["textures"])
        {
            m_resources->load_from_path<texture>(item["name"].get<std::string>(), item["path"].get<std::string>());
        }
    }

    if (res_json.contains("scripts"))
    {
        for (const auto& item : res_json["scripts"])
        {
            m_resources->load_from_path<script>(item.get<std::string>(), item.get<std::string>());
        }
    }

    if (res_json.contains("meshes"))
    {
        for (const auto& item : res_json["meshes"])
        {
            m_resources->load_from_path<mesh>(item["name"].get<std::string>(), item["path"].get<std::string>()); //TODO
        }
    }

    if (res_json.contains("materials"))
    {
        for (const auto& item : res_json["materials"])
        {
            auto mat = std::make_unique<material>();
            mat->set_shader(m_resources->get_handle<shader>(item["shader"].get<std::string>()));

            if (item.contains("textures"))
            {
                for (const auto& t : item["textures"])
                {
                    const auto texture_handle = m_resources->get_handle<texture>(t["value"].get<std::string>());
                    mat->set_texture(t["name"].get<std::string>(), texture_handle);
                }
            }

            if (item.contains("colors"))
            {
                for (const auto& c : item["colors"])
                {
                    const auto value = color_parser::parse(c["value"].get<std::string>());
                    mat->set_color(c["name"].get<std::string>(), value);
                }
            }

            if (item.contains("parameters"))
            {
                for (const auto& c : item["parameters"])
                {
                    mat->set_parameter(c["name"].get<std::string>(), c["value"].get<float>());
                }
            }

            m_resources->load_instance(item["name"].get<std::string>(), std::move(mat));
        }
    }
}

auto noi_engine::scene_parser::is_main_camera(const std::string& name) -> bool
{
    return "main_camera" == name;
}

auto noi_engine::scene_parser::parse_entities(scene& target_scene, const nlohmann::json& entities_json) const -> void
{
    for (const auto& entity_json : entities_json)
    {
        parse_entity(target_scene, entity_json);
    }
}

auto noi_engine::scene_parser::parse_entity(scene& target_scene, const nlohmann::json& entity_json) const -> void
{
    const auto entity_name = entity_json["name"].get<std::string>();

    entity entity;
    auto& world = target_scene.get_world();
    if (is_main_camera(entity_name))
    {
        entity = target_scene.get_camera_entity();
    }
    else
    {
        entity = world.create_entity();
    }

    world.add(entity, name_component{.name = entity_name});
    if (!entity_json.contains("components"))
    {
        return;
    }

    for (const auto& component_json : entity_json["components"])
    {
        parse_component(target_scene, entity, component_json);
    }
}

auto noi_engine::scene_parser::parse_component(scene& target_scene, const entity& entity,
                                               const nlohmann::json& comp_json) const -> void
{
    const auto type = comp_json.value("type", "");
    const auto& properties = comp_json.value("properties", nlohmann::json::object());

    if (type == "camera_2d")
    {
        camera_2d_parser parser{};
        parser.parse(entity, target_scene, m_resources, properties);
    }
    else if (type == "scripts")
    {
        script_component_parser parser{};
        parser.parse(entity, target_scene, m_resources, properties);
    }
    else if (type == "transform")
    {
        transform_parser parser{};
        parser.parse(entity, target_scene, m_resources, properties);
    }
    else if (type == "render_layer")
    {
        render_layer_parser parser{};
        parser.parse(entity, target_scene, m_resources, properties);
    }
    else if (type == "mesh_renderer")
    {
        mesh_renderer_parser parser{};
        parser.parse(entity, target_scene, m_resources, properties);
    }
    else if (type == "box_collider")
    {
        box_collider_parser parser{};
        parser.parse(entity, target_scene, m_resources, properties);
    }
    else if (type == "culling")
    {
        culling_parser parser{};
        parser.parse(entity, target_scene, m_resources, properties);
    }
    else if (type == "always_active")
    {
        always_active_parser parser{};
        parser.parse(entity, target_scene, m_resources, properties);
    }
}
