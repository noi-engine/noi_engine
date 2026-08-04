find_package(Qt6 REQUIRED COMPONENTS Quick)
qt_standard_project_setup(REQUIRES 6.10)

set(NOI_ENGINE_EDITOR_SOURCES
        main.cpp
)

set(NOI_ENGINE_EDITOR_PROJECT_NAME noi_engine_editor)

# TODO(begin): review
qt_add_executable(${NOI_ENGINE_EDITOR_PROJECT_NAME}
        main.cpp
)

qt_add_qml_module(${NOI_ENGINE_EDITOR_PROJECT_NAME}
        URI ${NOI_ENGINE_EDITOR_PROJECT_NAME}
        QML_FILES
        Main.qml
)

set_target_properties(${NOI_ENGINE_EDITOR_PROJECT_NAME} PROPERTIES
        #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appnoi_engine_editor
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)
# TODO(end): review

target_link_libraries(${NOI_ENGINE_EDITOR_PROJECT_NAME}
        PRIVATE Qt6::Quick
)

target_link_libraries(
        ${NOI_ENGINE_EDITOR_PROJECT_NAME}
        PRIVATE
        ${NOI_ENGINE_LIB_NAME}
)

target_include_directories(${NOI_ENGINE_EDITOR_PROJECT_NAME} PRIVATE ${NOI_ENGINE_SOURCE_DIR}/include)

set_target_properties(${NOI_ENGINE_EDITOR_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/editor/bin")