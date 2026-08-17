//
// Created by ricka on 8/16/26.
//

#pragma once

#include <nlohmann/json.hpp>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/resources/resources.hpp>

namespace noi_engine
{
    class scene_parser
    {
        resources* m_resources{nullptr};

    public:
        explicit scene_parser(resources* resources);

        [[nodiscard]] auto parse(const nlohmann::json& root_json) const -> std::unique_ptr<scene>;

        auto parse_resources(const nlohmann::json& res_json) const -> void;

        [[nodiscard]] static auto is_main_camera(const std::string& name) -> bool;

        auto parse_entity(scene& target_scene, const nlohmann::json& entity_json) const -> void;

        auto parse_entities(scene& target_scene, const nlohmann::json& entities_json) const -> void;

        auto parse_component(scene& target_scene, const entity& entity, const nlohmann::json& comp_json) const -> void;
    };
}
