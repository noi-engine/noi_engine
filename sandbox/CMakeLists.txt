set(SANDBOX_HEADERS
        sandbox_game.hpp
        basic/configure.hpp
        basic/scripts/scripts.hpp
)

set(SANDBOX_SOURCES
        main.cpp
        basic/configure.cpp
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