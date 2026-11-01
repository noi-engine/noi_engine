#include "culling_parser.hpp"

#include <noi_engine/core/components/culling.hpp>

namespace noi_engine
{
    auto culling_parser::parse(const entity& entity, scene& target_scene,
                               [[maybe_unused]] resources* resources,
                               const nlohmann::json& properties) -> void
    {
        culling value{};
        value.enabled = properties.value("enabled", value.enabled);
        value.margin = properties.value("margin", value.margin);
        value.simulate_offscreen = properties.value("simulate_offscreen", value.simulate_offscreen);
        target_scene.get_world().add<culling>(entity, value);
    }

    auto always_active_parser::parse(const entity& entity, scene& target_scene,
                                     [[maybe_unused]] resources* resources,
                                     [[maybe_unused]] const nlohmann::json& properties) -> void
    {
        target_scene.get_world().add<always_active>(entity, always_active{});
    }
} // namespace noi_engine
