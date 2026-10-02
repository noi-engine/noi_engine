#include "box_collider_parser.hpp"

#include <noi_engine/builtin/components/box_collider.hpp>

namespace noi_engine
{
    auto box_collider_parser::parse(const entity& entity, scene& target_scene,
                                    [[maybe_unused]] resources* resources,
                                    const nlohmann::json& properties) -> void
    {
        box_collider value{};

        if (properties.contains("half_extents"))
        {
            const auto half_extents = properties["half_extents"];
            value.half_extents = glm::vec2(half_extents[0].get<float>(), half_extents[1].get<float>());
        }

        value.is_static = properties.value("is_static", false);

        target_scene.get_world().add<box_collider>(entity, value);
    }
} // namespace noi_engine
