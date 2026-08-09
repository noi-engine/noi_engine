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
        basic/scenes/player_scene.cpp
        basic/scripts/player_script.cpp
        basic/scripts/camera_script.cpp
        basic/scripts/background_script.cpp
)

add_executable(sandbox ${SANDBOX_SOURCES})

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