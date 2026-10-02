#include "box_collider_parser.hpp"

#include "../fbs/scene_generated.h"
#include <noi_engine/builtin/components/box_collider.hpp>

namespace noi_engine::c
{
    auto box_collider_parser::parse(const entity& entity, scene& target_scene,
                                    [[maybe_unused]] resources* resources,
                                    const void* properties) -> void
    {
        box_collider value{};

        if (!properties)
        {
            target_scene.get_world().add<box_collider>(entity, value);
            return;
        }

        const auto box_collider_properties = static_cast<const fbs::BoxColliderComponent*>(properties);

        if (const auto* half_extents = box_collider_properties->half_extents())
        {
            if (half_extents->size() >= 2)
            {
                value.half_extents = glm::vec2(half_extents->Get(0), half_extents->Get(1));
            }
        }

        value.is_static = box_collider_properties->is_static();

        target_scene.get_world().add<box_collider>(entity, value);
    }
} // namespace noi_engine::c
