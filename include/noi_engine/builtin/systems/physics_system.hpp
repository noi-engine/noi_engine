//
// Created by ricka on 9/23/26.
//
#pragma once

#include <cstdint>
#include <map>
#include <utility>
#include <vector>

#include <noi_engine/core/components/culling.hpp>
#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/system.hpp>

namespace noi_engine
{
    // Gravity and box collisions.
    //
    //  - `gravity` makes an entity a moving body (and `gravity::grounded` tells when it rests on
    //    something).
    //  - `box_collider` makes it solid. Bodies are pushed out of other colliders; static boxes
    //    and boxes without gravity never move; triggers only report.
    //  - As a system added to a scene it also emits `collision_begin` / `collision_end` signals
    //    (see builtin/signals/collision_signals.hpp) when two colliders start / stop touching.
    class physics_system : public system
    {
    public:
        // One pair of overlapping colliders found by a step.
        struct contact
        {
            entity first;
            entity second;
            bool trigger;
        };

        static auto step(world& world, float dt) -> void;
        // Same, but bodies outside `active_area` (unless always_active) are left alone. Used when
        // the camera's culling has simulate_offscreen = false.
        static auto step(world& world, float dt, const view_area& active_area) -> void;
        // Same as the above (area may be null), and fills `contacts` with the overlapping pairs.
        static auto step(world& world, float dt, const view_area* active_area, std::vector<contact>& contacts) -> void;

        auto on_update(const script_context& ctx, float dt) -> void override;

        [[nodiscard]] auto name() const -> std::string_view override { return "physics_system"; }

    private:
        using pair_key = std::pair<std::uint64_t, std::uint64_t>;

        // Pairs touching after the previous step: what's new / gone now raises the signals.
        std::map<pair_key, bool> m_touching; // value: the pair involves a trigger
    };
}
