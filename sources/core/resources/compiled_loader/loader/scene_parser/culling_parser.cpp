#include "culling_parser.hpp"

#include "../fbs/scene_generated.h"
#include <noi_engine/core/components/culling.hpp>

namespace noi_engine::c
{
    auto culling_parser::parse(const entity& entity, scene& target_scene,
                               [[maybe_unused]] resources* resources,
                               const void* properties) -> void
    {
        culling value{};
        if (properties)
        {
            const auto* culling_properties = static_cast<const fbs::CullingComponent*>(properties);
            value.enabled = culling_properties->enabled();
            value.margin = culling_properties->margin();
            value.simulate_offscreen = culling_properties->simulate_offscreen();
        }
        target_scene.get_world().add<culling>(entity, value);
    }

    auto always_active_parser::parse(const entity& entity, scene& target_scene,
                                     [[maybe_unused]] resources* resources,
                                     [[maybe_unused]] const void* properties) -> void
    {
        target_scene.get_world().add<always_active>(entity, always_active{});
    }
} // namespace noi_engine::c
