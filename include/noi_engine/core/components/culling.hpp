#pragma once

#include <glm/vec2.hpp>
#include <noi_engine/core/components/component.hpp>
#include <noi_engine/core/ecs/entity.hpp>

namespace noi_engine
{
    class world;

    // On the scene camera: only what the camera sees (plus `margin` world units around it) is
    // drawn. With simulate_offscreen = false, physics also leaves the bodies outside that area
    // alone. Without this component nothing is culled.
    struct culling : component
    {
        bool enabled{true};
        float margin{2.0f};
        bool simulate_offscreen{true};
    };

    // On an entity: always drawn and simulated, even outside the camera's view (a large
    // background, something a script relies on...).
    struct always_active : component
    {
    };

    // World-space rectangle.
    struct view_area
    {
        glm::vec2 min{0.0f};
        glm::vec2 max{0.0f};

        [[nodiscard]] auto overlaps(const glm::vec2 centre, const glm::vec2 half_size) const -> bool
        {
            return centre.x + half_size.x >= min.x && centre.x - half_size.x <= max.x &&
                   centre.y + half_size.y >= min.y && centre.y - half_size.y <= max.y;
        }
    };

    // The area the camera's culling keeps active (what it sees + margin). False when the
    // camera has no enabled culling (or isn't a 2D camera): then everything is active.
    [[nodiscard]] auto culling_area(world& world, entity camera, view_area& area) -> bool;
}
