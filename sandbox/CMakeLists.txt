set(SANDBOX_HEADERS
        sandbox_game.hpp
        3d/resources/meshes.hpp
        3d/resources/shaders.hpp
        3d/configure.hpp
        3d/scenes/orbit_scene.hpp
        2d/resources/meshes.hpp
        2d/resources/shaders.hpp
        2d/configure.hpp
        2d/scenes/basic_scene.hpp
        basic/configure.hpp
        basic/components/velocity.hpp
        basic/components/player_controller.hpp
        basic/systems/player_controller_system.hpp
        basic/systems/movement_system.hpp
        basic/scripts/scripts.hpp
)

set(SANDBOX_SOURCES
        main.cpp
        3d/resources/meshes.cpp
        3d/resources/shaders.cpp
        3d/configure.cpp
        2d/resources/meshes.cpp
        2d/resources/shaders.cpp
        2d/configure.cpp
        basic/configure.cpp
        basic/systems/player_controller_system.cpp
        basic/systems/movement_system.cpp
        basic/scripts/player_script.cpp
        basic/scripts/camera_script.cpp
)

add_executable(sandbox ${SANDBOX_SOURCES} ${SANDBOX_HEADERS})

target_link_libraries(
        sandbox
        PRIVATE
        ${NOI_ENGINE_LIB_NAME}
)

target_include_directories(sandbox PRIVATE ${NOI_ENGINE_SOURCE_DIR}/include)

set_target_properties(sandbox PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(SANDBOX_ASSETS ${CMAKE_CURRENT_SOURCE_DIR}/assets)

add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/bin/assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SANDBOX_ASSETS}
        ${CMAKE_BINARY_DIR}/bin/assets
        DEPENDS ${SANDBOX_ASSETS}
)

add_custom_target(sandbox_assets DEPENDS ${CMAKE_BINARY_DIR}/bin/assets)

add_dependencies(sandbox sandbox_assets)