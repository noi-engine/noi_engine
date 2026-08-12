cmake_minimum_required(VERSION 3.18)

project(noi_engine VERSION 0.0.1 DESCRIPTION "noi_engine" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)

set(NOI_ENGINE_LIB_NAME noi_engine)
set(NOI_ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(NOI_ENGINE_IS_MAIN_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(NOI_ENGINE_IS_MAIN_PROJECT ON)
endif ()

set(NOI_ENGINE_VERSION ${PROJECT_VERSION})
set(NOI_ENGINE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})

if (NOI_ENGINE_IS_MAIN_PROJECT)
    configure_file(
            ${NOI_ENGINE_SOURCE_DIR}/.templates/${NOI_ENGINE_LIB_NAME}Config.hpp.in
            ${NOI_ENGINE_SOURCE_DIR}/include/${NOI_ENGINE_LIB_NAME}/${NOI_ENGINE_LIB_NAME}Config.hpp @ONLY)
endif ()

if (BUILD_SHARED_LIBS)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

add_subdirectory(noi_engine/lib)

option(NOI_ENGINE_BUILD_EDITOR "Build Noi Engine editor" ON)
if (NOI_ENGINE_BUILD_EDITOR)
    add_subdirectory(external/Templi)
    add_subdirectory(noi_engine/editor)
endif ()

option(NOI_ENGINE_BUILD_TESTS "Build Noi Engine tests" ON)
if (NOI_ENGINE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()

option(NOI_ENGINE_BUILD_SANDBOX "Build Noi Engine sandbox" ON)
if (NOI_ENGINE_BUILD_SANDBOX)
    add_subdirectory(sandbox)
endif ()

