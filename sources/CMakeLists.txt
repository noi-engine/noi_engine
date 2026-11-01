set(CORE_HEADERS
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/noi_engineConfig.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/model/vertex.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/model/mesh.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/model/shader.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/model/texture.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/model/material.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/model/script.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/ecs/entity.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/ecs/details/component_pool.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/ecs/details/view.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/mesh_renderer_properties.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/ecs/details/view_iterator.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/ecs/world.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/signals/signal.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/signals/details/signal_channel.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/signals/details/signal_bus.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/component.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/transform.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/world_matrix.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/mesh_renderer.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/sdl/sdl_game.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/sdl/sdl_window.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/render_layer.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/dirty.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/camera_2d.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/camera_3d.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/script_component.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/name_component.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/culling.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/resources/resource_handle.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/resources/resource_loader.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/resources/details/resource_manager.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/resources/resources.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/input/input_codes.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/input/input_state.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/renderer/renderer.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/frame_limiter.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/timer.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/scene.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/scene_manager.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/system.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/game.hpp
)

set(BUILTIN_HEADERS
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/builtin/actions/basic.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/builtin/components/gravity.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/builtin/components/box_collider.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/builtin/components/orbit_camera.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/builtin/systems/physics_system.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/builtin/systems/orbit_camera_system.hpp
)

set(CORE_PRIVATE_HEADERS
        core/glad/glad.h
        core/glad/khrplateform.h
        core/sdl/sdl_event_processor.hpp
        core/systems/render_system.hpp
        core/systems/camera_2d_system.hpp
        core/systems/camera_3d_system.hpp
        core/systems/camera_system.hpp
        core/ecs/entity_manager.hpp
        core/systems/transform_system.hpp
        core/systems/script_system.hpp
        core/systems/script_runner_system.hpp
        core/input/input_state_impl.hpp
        core/resources/source_loader/builtin_shaders.hpp
        core/resources/source_loader/builtin_meshes.hpp
        core/resources/source_loader/builtin_materials.hpp
        core/resources/compiled_loader/loader/fbs/shader_generated.h
        core/resources/compiled_loader/loader/fbs/mesh_2d_generated.h
        core/resources/compiled_loader/loader/fbs/scene_generated.h
        core/resources/compiled_loader/loader/shader_loader.hpp
        core/resources/compiled_loader/loader/scene_loader.hpp
        core/resources/compiled_loader/loader/scene_parser/scene_parser.hpp
        core/resources/compiled_loader/loader/scene_parser/component_parser.hpp
        core/resources/compiled_loader/loader/scene_parser/box_collider_parser.hpp
        core/resources/compiled_loader/loader/scene_parser/culling_parser.hpp
        core/resources/compiled_loader/loader/mesh_2d_loader.hpp
        core/resources/source_loader/loader/mesh_loader.hpp
        core/resources/source_loader/loader/scene_loader.hpp
        core/resources/source_loader/loader/shader_loader.hpp
        core/resources/source_loader/loader/texture_loader.hpp
        core/resources/source_loader/loader/mesh_2d_loader.hpp
        core/resources/source_loader/loader/scene_parser/color_parser.hpp
        core/resources/source_loader/loader/scene_parser/scene_parser.hpp
        core/resources/source_loader/loader/scene_parser/component_parser.hpp
        core/resources/source_loader/loader/scene_parser/box_collider_parser.hpp
        core/resources/source_loader/loader/scene_parser/culling_parser.hpp
)

set(CORE_SOURCES
        core/glad/glad.cpp
        core/game.cpp
        core/scene.cpp
        core/timer.cpp
        core/frame_limiter.cpp
        core/scene_manager.cpp
        core/renderer/renderer.cpp
        core/ecs/world.cpp
        core/ecs/entity_manager.cpp
        core/ecs/entity.cpp
        core/model/mesh.cpp
        core/model/texture.cpp
        core/model/shader.cpp
        core/model/scripts.cpp
        core/model/material.cpp
        core/input/input_state.cpp
        core/resources/resources.cpp
        core/components/world_matrix.cpp
        core/components/culling.cpp
        core/systems/render_system.cpp
        core/systems/camera_2d_system.cpp
        core/systems/camera_3d_system.cpp
        core/systems/camera_system.cpp
        core/systems/transform_system.cpp
        core/stb_image/stb_image.cpp
        core/signals/signal_bus.cpp
        core/systems/script_system.cpp
        core/systems/script_runner_system.cpp
        core/input/input_state_impl.cpp
        core/resources/source_loader/builtin_meshes.cpp
        core/resources/source_loader/builtin_materials.cpp
        core/resources/source_loader/builtin_shaders.cpp
        core/resources/compiled_loader/loader/shader_loader.cpp
        core/resources/compiled_loader/loader/mesh_2d_loader.cpp
        core/resources/compiled_loader/loader/scene_loader.cpp
        core/resources/compiled_loader/loader/scene_parser/scene_parser.cpp
        core/resources/compiled_loader/loader/scene_parser/component_parser.cpp
        core/resources/compiled_loader/loader/scene_parser/box_collider_parser.cpp
        core/resources/compiled_loader/loader/scene_parser/culling_parser.cpp
        core/resources/compiled_loader/compiled_resource_loader.cpp
        core/resources/source_loader/source_resource_loader.cpp
        core/resources/source_loader/loader/scene_loader.cpp
        core/resources/source_loader/loader/mesh_2d_loader.cpp
        core/resources/source_loader/loader/shader_loader.cpp
        core/resources/source_loader/loader/texture_loader.cpp
        core/resources/source_loader/loader/mesh_loader.cpp
        core/resources/source_loader/loader/scene_parser/color_parser.cpp
        core/resources/source_loader/loader/scene_parser/component_parser.cpp
        core/resources/source_loader/loader/scene_parser/box_collider_parser.cpp
        core/resources/source_loader/loader/scene_parser/culling_parser.cpp
        core/resources/source_loader/loader/scene_parser/scene_parser.cpp
        core/sdl/sdl_game.cpp
        core/sdl/sdl_window.cpp
        core/sdl/sdl_event_processor.cpp
)

set(NOI_ENGINE_BUILTIN_SOURCES
        builtin/actions/follow.cpp
        builtin/systems/physics_system.cpp
        builtin/systems/orbit_camera_system.cpp
)

set(NOI_ENGINE_SOURCES ${CORE_SOURCES} ${NOI_ENGINE_BUILTIN_SOURCES})

set(NOI_ENGINE_PUBLIC_HEADERS ${CORE_HEADERS} ${BUILTIN_HEADERS})

set(NOI_ENGINE_PRIVATE_HEADERS ${CORE_PRIVATE_HEADERS})

if (CMAKE_BUILD_SHARED_LIBS)
    add_library(${NOI_ENGINE_LIB_NAME} SHARED ${NOI_ENGINE_SOURCES})
else ()
    add_library(${NOI_ENGINE_LIB_NAME} STATIC ${NOI_ENGINE_SOURCES})
endif ()

target_sources(${NOI_ENGINE_LIB_NAME}
        PUBLIC
        FILE_SET public_headers
        TYPE HEADERS
        BASE_DIRS ${NOI_ENGINE_SOURCE_DIR}/include
        FILES ${NOI_ENGINE_PUBLIC_HEADERS}
)

target_sources(${NOI_ENGINE_LIB_NAME}
        PRIVATE
        FILE_SET private_headers
        TYPE HEADERS
        BASE_DIRS ${NOI_ENGINE_SOURCE_DIR}/sources
        FILES ${NOI_ENGINE_PRIVATE_HEADERS}
)
target_include_directories(${NOI_ENGINE_LIB_NAME} PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(${NOI_ENGINE_LIB_NAME}
        PUBLIC
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

target_link_libraries(${NOI_ENGINE_LIB_NAME} PUBLIC glm::glm)

target_link_libraries(${NOI_ENGINE_LIB_NAME} PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(
        ${NOI_ENGINE_LIB_NAME} PUBLIC
        $<BUILD_INTERFACE:${NOI_ENGINE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(${NOI_ENGINE_LIB_NAME} PRIVATE tinyobjloader::tinyobjloader)

target_link_libraries(${NOI_ENGINE_LIB_NAME} PRIVATE flatbuffers::flatbuffers)

set_target_properties(
        ${NOI_ENGINE_LIB_NAME}
        PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/libs"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/libs"
        SOVERSION ${NOI_ENGINE_VERSION_MAJOR}
        VERSION ${NOI_ENGINE_VERSION})