#pragma once

#include "component_parser.hpp"

namespace noi_engine
{
    class box_collider_parser final : public i_component_parser
    {
    public:
        auto parse(const entity& entity, scene& target_scene,
                   resources* resources, const nlohmann::json& properties)
            -> void override;
    };
} // namespace noi_engine
