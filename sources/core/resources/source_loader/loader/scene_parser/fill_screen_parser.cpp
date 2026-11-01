#include "fill_screen_parser.hpp"

#include <noi_engine/core/components/fill_screen.hpp>

namespace noi_engine
{
    auto fill_screen_parser::parse(const entity& entity, scene& target_scene,
                                   [[maybe_unused]] resources* resources,
                                   [[maybe_unused]] const nlohmann::json& properties) -> void
    {
        target_scene.get_world().add<fill_screen>(entity, fill_screen{});
    }
} // namespace noi_engine
