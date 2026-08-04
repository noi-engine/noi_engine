//
// Created by ricka on 8/2/26.
//

#include <gtest/gtest.h>

#include <SDL2/SDL_events.h>
#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/components/camera_2d.hpp>
#include <noi_engine/core/components/camera_2d_debug_controller.hpp>
#include <noi_engine/core/components/transform.hpp>
#include <noi_engine/core/components/dirty.hpp>
#include <noi_engine/core/input/input_state.hpp>
#include <lib/core/systems/camera_2d_debug_controller_system.hpp>

using namespace noi_engine;

TEST(Camera2dDebugControllerSystemTest, ScrollZoomsInAndClamps)
{
    world w;
    input_state input;

    const auto camera = w.create_entity();
    w.add(camera, transform{});
    w.add(camera, camera_2d{.zoom = 1.0f});
    w.add(camera, camera_2d_debug_controller{.zoom_speed = 0.5f, .min_zoom = 0.1f, .max_zoom = 2.0f});

    input.begin_frame();

    SDL_Event scroll{};
    scroll.type = SDL_MOUSEWHEEL;
    scroll.wheel.y = 3;
    input.process_event(scroll);

    camera_2d_debug_controller_system::update(w, camera, input);

    EXPECT_FLOAT_EQ(w.get<camera_2d>(camera).zoom, 2.0f);
}

TEST(Camera2dDebugControllerSystemTest, MiddleMousePansTransform)
{
    world w;
    input_state input;

    const auto camera = w.create_entity();
    w.add(camera, transform{});
    w.add(camera, camera_2d{.zoom = 1.0f});
    w.add(camera, camera_2d_debug_controller{.pan_sensitivity = 1.0f});

    input.begin_frame();

    SDL_Event button_down{};
    button_down.type = SDL_MOUSEBUTTONDOWN;
    button_down.button.button = SDL_BUTTON_MIDDLE;
    input.process_event(button_down);

    SDL_Event motion{};
    motion.type = SDL_MOUSEMOTION;
    motion.motion.xrel = 10;
    motion.motion.yrel = 5;
    input.process_event(motion);

    camera_2d_debug_controller_system::update(w, camera, input);

    const auto& position = w.get<transform>(camera).position;

    EXPECT_FLOAT_EQ(position.x, -10.0f);
    EXPECT_FLOAT_EQ(position.y, 5.0f);
    EXPECT_TRUE(w.has<dirty<transform>>(camera));
}
