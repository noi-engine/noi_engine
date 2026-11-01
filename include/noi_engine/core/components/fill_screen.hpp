#pragma once

#include <noi_engine/core/components/component.hpp>
#include <noi_engine/core/ecs/entity.hpp>

namespace noi_engine
{
    class world;

    // On an entity with a transform: every frame, before drawing, it is placed on the camera and
    // sized to exactly what the camera sees (the whole window), whatever the camera does. Made
    // for backgrounds. Its own position / scale are overwritten (its z and rotation are kept).
    struct fill_screen : component
    {
    };

    // Places and sizes every fill_screen entity on what the 2D camera sees. No-op if the camera
    // isn't a 2D camera with a transform. Called by the render system before drawing.
    auto apply_fill_screen(world& world, entity camera) -> void;
}
