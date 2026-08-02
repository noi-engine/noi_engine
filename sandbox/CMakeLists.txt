set(SANDBOX_SOURCES
        main.cpp
        3d/resources/meshes.cpp
        3d/resources/shaders.cpp
        3d/configure.cpp
        2d/resources/meshes.cpp
        2d/resources/shaders.cpp
        2d/configure.cpp
)

add_executable(sandbox ${SANDBOX_SOURCES})

target_link_libraries(
        sandbox
        PRIVATE
        ${NOI_ENGINE_LIB_NAME}
)

target_include_directories(sandbox PRIVATE ${NOI_ENGINE_SOURCE_DIR}/include)

set_target_properties(sandbox PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

