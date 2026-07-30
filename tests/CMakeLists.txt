find_package(GTest CONFIG REQUIRED)

set(NOI_ENGINE_TEST_SOURCES
        core/core_sum_test.cpp
        core/core_window_test.cpp
)

add_executable(noi_engine_tests ${NOI_ENGINE_TEST_SOURCES})

target_link_directories(noi_engine_tests PRIVATE ${CMAKE_BINARY_DIR}/lib)
target_link_libraries(
        noi_engine_tests
        PRIVATE
        ${NOI_ENGINE_LIB_NAME}
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(noi_engine_tests)
