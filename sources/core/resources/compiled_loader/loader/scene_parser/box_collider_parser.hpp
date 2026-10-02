#pragma once

#include "component_parser.hpp"

namespace noi_engine::c
{
    class box_collider_parser final : public i_component_parser
    {
    public:
        auto parse(const entity& entity, scene& target_scene,
                   resources* resources, const void* properties)
            -> void override;
    };
} // namespace noi_engine::c
