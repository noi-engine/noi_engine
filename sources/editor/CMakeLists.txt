set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(NOI_ENGINE_EDITOR_PROJECT_NAME noi_engine_editor)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

# TODO(begin): review
qt_add_executable(${NOI_ENGINE_EDITOR_PROJECT_NAME} resources.qrc main.cpp)

set(NOI_ENGINE_EDITOR_QML_SINGLETONS
        sources/Router.qml
        sources/components/Theme.qml
        sources/components/icons/IconLoader.qml
        sources/components/fonts/CustomFont.qml
)

set_source_files_properties(${NOI_ENGINE_EDITOR_QML_SINGLETONS} PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(${NOI_ENGINE_EDITOR_PROJECT_NAME}
        URI noi_engine_editor
        QML_FILES
        Main.qml
        ${NOI_ENGINE_EDITOR_QML_SINGLETONS}
        sources/components/icons/IconLoaderCreator.js
        sources/components/icons/MaterialSymbolsRegular/codepoints.js
        sources/components/icons/MuiIcon.qml
        sources/components/CustomPage.qml
        sources/pages/MainPage.qml
        SOURCES
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
        PRIVATE
        Qt6::Quick
        ${NOI_ENGINE_LIB_NAME}
)

target_include_directories(${NOI_ENGINE_EDITOR_PROJECT_NAME} PRIVATE ${NOI_ENGINE_SOURCE_DIR}/include)

set_target_properties(${NOI_ENGINE_EDITOR_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/editor/bin")