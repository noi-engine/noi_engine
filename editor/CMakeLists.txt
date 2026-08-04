set(NOI_ENGINE_EDITOR_SOURCES
        main.cpp
)

set(NOI_ENGINE_EDITOR_PROJECT_NAME noi_engine_editor)

add_executable(noi_engine_editor ${NOI_ENGINE_EDITOR_SOURCES})

target_link_libraries(
        noi_engine_editor
        PRIVATE
        ${NOI_ENGINE_LIB_NAME}
)

target_include_directories(noi_engine_editor PRIVATE ${NOI_ENGINE_SOURCE_DIR}/include)

set_target_properties(noi_engine_editor PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/editor/bin")