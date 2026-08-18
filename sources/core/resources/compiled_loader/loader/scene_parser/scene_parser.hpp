//
// Created by ricka on 8/16/26.
//

#pragma once

#include "../fbs/scene_generated.h"
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/resources/resources.hpp>

namespace noi_engine::c
{
    class scene_parser
    {
        resources* m_resources{nullptr};

    public:
        explicit scene_parser(resources* resources);

        [[nodiscard]] auto parse(const fbs::Scene* root) const -> std::unique_ptr<scene>;

        auto parse_resources(const fbs::Resources* res) const -> void;

        [[nodiscard]] static auto is_main_camera(const std::string& name) -> bool;

        auto parse_entity(scene& target_scene, const fbs::Entity* entity_fbs) const -> void;

        auto parse_entities(scene& target_scene, const flatbuffers::Vector<flatbuffers::Offset<fbs::Entity>>* entities) const -> void;

        auto parse_component(scene& target_scene, const entity& entity, const fbs::Component* comp) const -> void;
    };
}
