set(SANBOX_SOURCES
        main.cpp
)

add_executable(sandbox ${SANBOX_SOURCES})

target_link_libraries(
        sandbox
        PRIVATE
        ${NOI_ENGINE_LIB_NAME}
)

target_include_directories(sandbox PRIVATE ${NOI_ENGINE_SOURCE_DIR}/include)
