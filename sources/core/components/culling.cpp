#include <noi_engine/core/components/culling.hpp>

#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/ecs/world.hpp>

auto noi_engine::culling_area(world& world, const entity camera, view_area& area) -> bool
{
    if (!world.has<culling>(camera) || !world.has<camera_2d>(camera) || !world.has<transform>(camera))
    {
        return false;
    }

    const auto& settings = world.get<culling>(camera);
    if (!settings.enabled)
    {
        return false;
    }

    const auto& cam = world.get<camera_2d>(camera);
    const auto& position = world.get<transform>(camera).position;
    const float half_height = cam.orthographic_size / cam.zoom + settings.margin;
    const float half_width = cam.orthographic_size / cam.zoom * cam.aspect_ratio + settings.margin;

    area.min = {position.x - half_width, position.y - half_height};
    area.max = {position.x + half_width, position.y + half_height};
    return true;
}
