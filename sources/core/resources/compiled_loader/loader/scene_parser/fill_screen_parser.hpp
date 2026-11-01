#pragma once

#include "component_parser.hpp"

namespace noi_engine::c
{
    // "fill_screen": the entity always covers what the camera sees (see fill_screen.hpp).
    class fill_screen_parser final : public i_component_parser
    {
    public:
        auto parse(const entity& entity, scene& target_scene,
                   resources* resources, const void* properties)
            -> void override;
    };
} // namespace noi_engine::c
