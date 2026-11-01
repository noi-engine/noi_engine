#pragma once

#include "component_parser.hpp"

namespace noi_engine::c
{
    // "culling" (on the scene camera) and "always_active" (on any entity), see culling.hpp.
    class culling_parser final : public i_component_parser
    {
    public:
        auto parse(const entity& entity, scene& target_scene,
                   resources* resources, const void* properties)
            -> void override;
    };

    class always_active_parser final : public i_component_parser
    {
    public:
        auto parse(const entity& entity, scene& target_scene,
                   resources* resources, const void* properties)
            -> void override;
    };
} // namespace noi_engine::c
