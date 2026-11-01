#include <noi_engine/core/components/fill_screen.hpp>

#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/world_matrix.hpp>
#include <noi_engine/core/ecs/world.hpp>

auto noi_engine::apply_fill_screen(world& world, const entity camera) -> void
{
    if (!world.has<camera_2d>(camera) || !world.has<transform>(camera))
    {
        return;
    }

    const auto& cam = world.get<camera_2d>(camera);
    const auto& camera_position = world.get<transform>(camera).position;
    // Same view as camera_2d_system: orthographic_size half-height, divided by the zoom.
    const float height = cam.orthographic_size * 2.0f / cam.zoom;
    const float width = height * cam.aspect_ratio;

    for (const auto e : world.view<fill_screen, transform>())
    {
        auto& tr = world.get<transform>(e);
        tr.position.x = camera_position.x;
        tr.position.y = camera_position.y;
        tr.scale = glm::vec3{width, height, 1.0f};

        // The transform system already ran this frame: update the matrix directly.
        if (world.has<world_matrix>(e))
        {
            world.get<world_matrix>(e).value = world_matrix::from(tr);
        }
        else
        {
            world.add<world_matrix>(e, world_matrix{.value = world_matrix::from(tr)});
        }
    }
}
