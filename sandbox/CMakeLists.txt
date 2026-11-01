set(SANDBOX_HEADERS
        sandbox_game.hpp
        configure.hpp
        scripts/scripts.hpp
        systems/bounds_system.hpp
        systems/entity_counter_system.hpp
        systems/fps_counter_system.hpp
)

set(SANDBOX_SOURCES
        main.cpp
        configure.cpp
        scripts/player_script.cpp
        scripts/camera_script.cpp
        systems/bounds_system.cpp
        systems/entity_counter_system.cpp
        systems/fps_counter_system.cpp
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