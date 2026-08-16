//
// Created by ricka on 8/16/26.
//

#pragma once

#include <nlohmann/json.hpp>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/resources/resource_system.hpp>

namespace noi_engine
{
    class scene_parser
    {
        resource_system* m_resources{nullptr};

    public:
        explicit scene_parser(resource_system* resources);

        [[nodiscard]] auto parse(const nlohmann::json& root_json) -> std::unique_ptr<scene>;

        auto parse_resources(const nlohmann::json& res_json) const -> void;

        [[nodiscard]] static auto is_main_camera(const std::string& name) -> bool;

        auto parse_entity(scene& target_scene, const nlohmann::json& entity_json) -> void;

        auto parse_entities(scene& target_scene, const nlohmann::json& entities_json) -> void;

        auto parse_component(scene& target_scene, const entity& entity, const nlohmann::json& comp_json) -> void;
    };
}
