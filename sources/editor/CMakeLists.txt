set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(NOI_ENGINE_EDITOR_PROJECT_NAME noi_engine_editor)
set(QML_IMPORT_PATH "${CMAKE_BINARY_DIR}/sources/editor" CACHE STRING "QML Import Path" FORCE)

find_package(Qt6 REQUIRED COMPONENTS Quick OpenGL)

qt_standard_project_setup(REQUIRES 6.10)
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
        VERSION 0.0.1
        QML_FILES
        Main.qml
        ${NOI_ENGINE_EDITOR_QML_SINGLETONS}

        # components
        sources/components/icons/IconLoaderCreator.js
        sources/components/icons/MaterialSymbolsRegular/codepoints.js
        sources/components/icons/MuiIcon.qml
        sources/components/CustomPage.qml
        sources/components/AppButton.qml
        sources/components/IconBadge.qml
        sources/components/SearchField.qml

        # Pages
        sources/pages/OpenglTestPage.qml
        sources/pages/CreateProjectPage.qml
        sources/pages/ProjectEditorPage.qml
        sources/pages/HomePage.qml

        # home
        sources/components/home/ActionCard.qml
        sources/components/home/EmptyState.qml
        sources/components/home/HeroHeader.qml
        sources/components/home/RecentProjectItem.qml
        sources/components/home/RecentProjectsSection.qml
        sources/components/home/QuickActionsRow.qml

        SOURCES
        # components
        sources/components/OpenglView.hpp
        sources/components/OpenglView.cpp
        sources/components/OpenglRenderer.hpp
        sources/components/OpenglRenderer.cpp

        #managers
        sources/managers/ProjectInfo.hpp
        sources/managers/RecentProjectsManager.hpp
        sources/managers/RecentProjectsManager.cpp
        sources/managers/SettingsManager.hpp
        sources/managers/SettingsManager.cpp
        sources/managers/ProjectCreator.hpp
        sources/managers/ProjectCreator.cpp
        sources/managers/CurrentProjectManager.hpp
        sources/managers/CurrentProjectManager.cpp

        # home
        sources/components/home/RecentProjectsModel.hpp
        sources/components/home/RecentProjectsModel.cpp
)

set_target_properties(${NOI_ENGINE_EDITOR_PROJECT_NAME} PROPERTIES
        #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appnoi_engine_editor
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

# TODO(begin): find a better way
file(GLOB_RECURSE ALL_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/sources/*.hpp")

set(INCLUDE_DIRS "")
foreach(HEADER_FILE ${ALL_HEADERS})
    get_filename_component(HEADER_DIR ${HEADER_FILE} DIRECTORY)
    list(APPEND INCLUDE_DIRS ${HEADER_DIR})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

target_include_directories(${NOI_ENGINE_EDITOR_PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${INCLUDE_DIRS}
    ${NOI_ENGINE_SOURCE_DIR}/include
)
# TODO(end): find a better way

target_link_libraries(${NOI_ENGINE_EDITOR_PROJECT_NAME}
    PRIVATE
    Qt6::Quick
    Qt6::OpenGL
    ${NOI_ENGINE_LIB_NAME}
)

set_target_properties(${NOI_ENGINE_EDITOR_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/editor/bin")