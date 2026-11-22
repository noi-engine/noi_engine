#pragma once

#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/signals/signal.hpp>

namespace noi_engine
{
    // Emitted by physics_system on the frame two colliders start overlapping, once for each of
    // the two entities (`source` is the entity you listen on, `other` the one it touched).
    // `trigger` is true when one of them is a trigger (nothing is pushed, it only reports).
    struct collision_begin : signal
    {
        entity other;
        bool trigger;

        constexpr collision_begin(const entity self, const entity touched, const bool is_trigger)
            : signal(self), other(touched), trigger(is_trigger)
        {
        }
    };

    // Same, on the frame they stop overlapping.
    struct collision_end : signal
    {
        entity other;
        bool trigger;

        constexpr collision_end(const entity self, const entity touched, const bool is_trigger)
            : signal(self), other(touched), trigger(is_trigger)
        {
        }
    };
}
