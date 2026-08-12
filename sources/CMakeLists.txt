set(CORE_HEADERS
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/noi_engineConfig.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/model/size_2d.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/model/vertex.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/model/mesh.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/model/shader.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/model/texture.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/model/material.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/ecs/entity.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/ecs/details/component_pool.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/ecs/details/view.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/ecs/details/view_iterator.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/ecs/world.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/signals/signal.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/signals/details/signal_channel.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/signals/details/signal_bus.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/scripts/script.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/component.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/transform.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/world_matrix.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/mesh_renderer.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/render_layer.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/dirty.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/camera_2d.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/camera_3d.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/orbit_camera.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/components/script_component.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/resources/resource_handle.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/resources/details/resource_manager.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/resources/resource_system.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/assets/asset_provider.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/input/input_codes.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/input/input_state.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/renderer/renderer.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/frame_limiter.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/timer.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/scene.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/scene_manager.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/core/game.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/builtin/signals/moved_signal.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/builtin/actions/action_context.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/builtin/actions/basic.hpp
)

set(CORE_PRIVATE_HEADERS
        core/glad/glad.h
        core/glad/khrplateform.h
        sdl/sdl_event_processor.hpp
        core/systems/render_system.hpp
        core/systems/orbit_camera_system.hpp
        core/systems/camera_2d_system.hpp
        core/systems/camera_3d_system.hpp
        core/ecs/entity_manager.hpp
        core/systems/transform_system.hpp
        core/systems/script_system.hpp
        core/assets/filesystem_asset_provider.hpp
        core/assets/texture_loader.hpp
        core/assets/mesh_loader.hpp
        core/input/input_state_impl.hpp
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
        core/model/mesh.cpp
        core/model/texture.cpp
        core/model/shader.cpp
        core/model/material.cpp
        core/input/input_state.cpp
        core/components/world_matrix.cpp
        core/systems/render_system.cpp
        core/systems/orbit_camera_system.cpp
        core/systems/camera_2d_system.cpp
        core/systems/camera_3d_system.cpp
        core/systems/transform_system.cpp
        core/assets/filesystem_asset_provider.cpp
        core/assets/texture_loader.cpp
        core/resource_system.cpp
        core/stb_image/stb_image.cpp
        core/assets/mesh_loader.cpp
        core/signals/signal_bus.cpp
        core/scripts/scripts.cpp
        core/systems/script_system.cpp
        core/ecs/entity.cpp
        core/input/input_state_impl.cpp
)

set(NOI_ENGINE_SDL_HEADERS
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/sdl/sdl_window.hpp
        ${NOI_ENGINE_SOURCE_DIR}/include/noi_engine/sdl/sdl_game.hpp
)

set(NOI_ENGINE_SDL_SOURCES
        sdl/sdl_game.cpp
        sdl/sdl_window.cpp
        sdl/sdl_event_processor.cpp
)

set(NOI_ENGINE_BUILTIN_SOURCES
        builtin/actions/follow.cpp
)

set(NOI_ENGINE_SOURCES
        ${CORE_SOURCES}
        ${NOI_ENGINE_SDL_SOURCES}
        ${NOI_ENGINE_BUILTIN_SOURCES})

set(NOI_ENGINE_PUBLIC_HEADERS
        ${CORE_HEADERS}
        ${NOI_ENGINE_SDL_HEADERS})

set(NOI_ENGINE_PRIVATE_HEADERS
        ${CORE_PRIVATE_HEADERS}
)

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

target_include_directories(
        ${NOI_ENGINE_LIB_NAME} PUBLIC $<BUILD_INTERFACE:${NOI_ENGINE_SOURCE_DIR}/include>)

target_link_libraries(${NOI_ENGINE_LIB_NAME} PRIVATE tinyobjloader::tinyobjloader)

set_target_properties(
        ${NOI_ENGINE_LIB_NAME}
        PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        SOVERSION ${NOI_ENGINE_VERSION_MAJOR}
        VERSION ${NOI_ENGINE_VERSION})