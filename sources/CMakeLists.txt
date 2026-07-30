set(CORE_SOURCES
        core/glad/glad.cpp
        core/game.cpp
        core/window.cpp
        core/scene.cpp
        core/timer.cpp
        core/frame_limiter.cpp
        core/scene_manager.cpp
        core/renderer/renderer.cpp
        core/ecs/world.cpp
        core/ecs/entity_manager.cpp
)

set(NOI_ENGINE_SOURCES
        ${CORE_SOURCES}
)

if (BUILD_SHARED_LIBS)
    add_library(${NOI_ENGINE_LIB_NAME} SHARED ${NOI_ENGINE_SOURCES})
else ()
    add_library(${NOI_ENGINE_LIB_NAME} STATIC ${NOI_ENGINE_SOURCES})
endif ()

target_link_libraries(${NOI_ENGINE_LIB_NAME}
        PUBLIC
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

target_include_directories(
        ${NOI_ENGINE_LIB_NAME} PUBLIC $<BUILD_INTERFACE:${NOI_ENGINE_SOURCE_DIR}/include>)

set_target_properties(
        ${NOI_ENGINE_LIB_NAME}
        PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        SOVERSION ${NOI_ENGINE_VERSION_MAJOR}
        VERSION ${NOI_ENGINE_VERSION})