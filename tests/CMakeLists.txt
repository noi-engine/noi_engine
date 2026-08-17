find_package(GTest CONFIG REQUIRED)

set(NOI_ENGINE_TEST_SOURCES
        core/sdl/sdl_window_test.cpp
        core/frame_limiter_test.cpp
        core/ecs/entity_manager_test.cpp
        core/ecs/entity_test.cpp
        core/ecs/world_test.cpp
        core/ecs/component_pool_test.cpp
        core/ecs/view_test.cpp
        core/systems/transform_system_test.cpp
        core/systems/render_system_test.cpp
)

add_executable(noi_engine_tests ${NOI_ENGINE_TEST_SOURCES})

target_include_directories(noi_engine_tests PRIVATE ${NOI_ENGINE_SOURCE_DIR}/sources)

target_link_directories(noi_engine_tests PRIVATE ${CMAKE_BINARY_DIR}/lib)
target_link_libraries(
        noi_engine_tests
        PRIVATE
        ${NOI_ENGINE_LIB_NAME}
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(noi_engine_tests)
