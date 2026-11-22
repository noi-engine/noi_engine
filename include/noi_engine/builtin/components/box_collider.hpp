//
// Created by ricka on 9/23/26.
//

#pragma once

#include <cstdint>
#include <glm/vec2.hpp>
#include <noi_engine/core/components/component.hpp>

namespace noi_engine
{
    // An axis-aligned box that physics_system keeps other boxes out of.
    //
    // - is_static:  the box never moves (floors, walls). Only bodies with `gravity` move.
    // - is_trigger: nothing is pushed apart, the overlap is only reported through
    //               collision_begin / collision_end (coins, doors, damage zones...).
    // - offset:     the box's centre relative to the entity's position.
    // - layer/mask: which group this box belongs to (a bit mask) and which groups it collides
    //               with. Two boxes interact only if each one's mask contains the other's layer.
    struct box_collider : component
    {
        glm::vec2 half_extents{0.5f, 0.5f};
        glm::vec2 offset{0.0f, 0.0f};
        bool is_static{false};
        bool is_trigger{false};
        std::uint32_t layer{1u};
        std::uint32_t mask{0xFFFFFFFFu};
    };
}
