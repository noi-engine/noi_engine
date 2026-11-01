//
// Created by ricka on 8/16/26.
//

#include "scene_parser.hpp"
#include "component_parser.hpp"
#include "box_collider_parser.hpp"
#include "culling_parser.hpp"
#include <noi_engine/core/components/name_component.hpp>
#include "../../../source_loader/loader/scene_parser/color_parser.hpp"

noi_engine::c::scene_parser::scene_parser(resources* resources) : m_resources(resources)
{
}

auto noi_engine::c::scene_parser::parse(const fbs::Scene* root) const -> std::unique_ptr<scene>
{
    auto loaded_scene = std::make_unique<scene>(root->name()->c_str());

    if (root->resources())
    {
        parse_resources(root->resources());
    }

    if (root->entities())
    {
        parse_entities(*loaded_scene, root->entities());
    }

    return loaded_scene;
}

auto noi_engine::c::scene_parser::parse_resources(const fbs::Resources* res) const -> void
{
    if (res->shaders())
    {
        for (const auto item : *res->shaders())
        {
            m_resources->load_from_path<shader>(item->name()->c_str(), item->path()->c_str());
        }
    }

    if (res->textures())
    {
        for (const auto item : *res->textures())
        {
            m_resources->load_from_path<texture>(item->name()->c_str(), item->path()->c_str());
        }
    }

    if (res->scripts())
    {
        for (const auto item : *res->scripts())
        {
            m_resources->load_from_path<script>(item->c_str());
        }
    }

    if (res->meshes())
    {
        for (const auto item : *res->meshes())
        {
            m_resources->load_from_path<mesh>(item->name()->c_str(), item->path()->c_str()); //TODO
        }
    }

    if (res->materials())
    {
        for (const auto item : *res->materials())
        {
            auto mat = std::make_unique<material>();
            mat->set_shader(m_resources->get_handle<shader>(item->shader()->c_str()));

            if (item->textures())
            {
                for (const auto t : *item->textures())
                {
                    const auto texture_handle = m_resources->get_handle<texture>(t->value()->c_str());
                    mat->set_texture(t->name()->c_str(), texture_handle);
                }
            }

            if (item->colors())
            {
                for (const auto c : *item->colors())
                {
                    const auto value = color_parser::parse(c->value()->c_str());
                    mat->set_color(c->name()->c_str(), value);
                }
            }

            if (item->parameters())
            {
                for (const auto c : *item->parameters())
                {
                    mat->set_parameter(c->name()->c_str(), c->value());
                }
            }

            m_resources->load_instance(item->name()->c_str(), std::move(mat));
        }
    }
}

auto noi_engine::c::scene_parser::is_main_camera(const std::string& name) -> bool
{
    return "main_camera" == name;
}

auto noi_engine::c::scene_parser::parse_entities(scene& target_scene,
                                                 const flatbuffers::Vector<flatbuffers::Offset<fbs::Entity>>* entities)
const -> void
{
    for (const auto entity_json : *entities)
    {
        parse_entity(target_scene, entity_json);
    }
}

auto noi_engine::c::scene_parser::parse_entity(scene& target_scene, const fbs::Entity* entity_fbs) const -> void
{
    const std::string entity_name = entity_fbs->name()->c_str();

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
    if (!entity_fbs->components())
    {
        return;
    }

    for (const auto component_json : *entity_fbs->components())
    {
        parse_component(target_scene, entity, component_json);
    }
}

auto noi_engine::c::scene_parser::parse_component(scene& target_scene, const entity& entity,
                                                  const fbs::Component* comp) const -> void
{
    const std::string type = comp->type()->c_str();
    const auto properties = comp->properties();

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
