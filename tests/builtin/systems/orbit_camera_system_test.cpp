//
// Created by ricka on 9/25/26.
//

#include <gtest/gtest.h>

#include <noi_engine/builtin/systems/orbit_camera_system.hpp>
#include <noi_engine/builtin/components/orbit_camera.hpp>
#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/input/input_state.hpp>
#include <noi_engine/core/scene.hpp>
#include <glm/matrix.hpp>

using namespace noi_engine;

TEST(OrbitCameraSystemTest, DragRotatesYawAndPitch)
{
    world w;
    const auto e = w.create_entity();
    w.add(e, orbit_camera{});

    input_state input;
    input.set_mouse_position({0.0f, 0.0f});
    input.set_mouse_button_pressed(mouse_button::left);
    input.set_mouse_position({10.0f, 5.0f});

    orbit_camera_system::update(w, e, input);

    const auto& cam = w.get<orbit_camera>(e);
    EXPECT_LT(cam.yaw, 0.0f);
    EXPECT_LT(cam.pitch, 0.2f);
}

TEST(OrbitCameraSystemTest, WithoutDragDoesNotRotate)
{
    world w;
    const auto e = w.create_entity();
    w.add(e, orbit_camera{});

    input_state input;
    input.set_mouse_position({0.0f, 0.0f});
    input.set_mouse_position({50.0f, 50.0f});

    orbit_camera_system::update(w, e, input);

    const auto& cam = w.get<orbit_camera>(e);
    EXPECT_FLOAT_EQ(cam.yaw, 0.0f);
    EXPECT_FLOAT_EQ(cam.pitch, 0.2f);
}

TEST(OrbitCameraSystemTest, ScrollZoomsWithinDistanceBounds)
{
    world w;
    const auto e = w.create_entity();
    w.add(e, orbit_camera{.distance = 5.0f, .min_distance = 1.0f, .max_distance = 50.0f});

    input_state input;
    input.add_scroll_delta(-100.0f);

    orbit_camera_system::update(w, e, input);

    EXPECT_FLOAT_EQ(w.get<orbit_camera>(e).distance, 50.0f);
}

TEST(OrbitCameraSystemTest, ViewMatrixLooksAtTargetFromOrbitPosition)
{
    world w;
    const auto e = w.create_entity();
    w.add(e, orbit_camera{.target = {0.0f, 0.0f, 0.0f}, .distance = 5.0f, .yaw = 0.0f, .pitch = 0.0f});

    const auto view = orbit_camera_system::view_matrix(w, e);
    const auto camera_position = glm::vec3{glm::inverse(view)[3]};

    EXPECT_NEAR(camera_position.x, 0.0f, 1e-4f);
    EXPECT_NEAR(camera_position.y, 0.0f, 1e-4f);
    EXPECT_NEAR(camera_position.z, 5.0f, 1e-4f);
}

TEST(OrbitCameraSystemTest, OnUpdateIsNoOpWhenCameraEntityHasNoOrbitCamera)
{
    scene s{"test"};
    input_state input;

    const script_context ctx{.scene = &s, .input = &input};

    orbit_camera_system orbit{};
    EXPECT_NO_THROW(orbit.on_update(ctx, 0.016f));
}

TEST(OrbitCameraSystemTest, OnUpdateMutatesTheSceneCameraEntityWhenOptedIn)
{
    scene s{"test"};
    s.get_world().add(s.get_camera_entity(), orbit_camera{});

    input_state input;
    input.add_scroll_delta(-100.0f);

    const script_context ctx{.scene = &s, .input = &input};

    orbit_camera_system orbit{};
    orbit.on_update(ctx, 0.016f);

    EXPECT_FLOAT_EQ(s.get_world().get<orbit_camera>(s.get_camera_entity()).distance, 50.0f);
}
