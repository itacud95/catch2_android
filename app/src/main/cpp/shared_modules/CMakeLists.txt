cmake_minimum_required(VERSION 3.22.1)

project(modules)

add_library(test_discovery OBJECT test_discovery.cpp)
target_link_libraries(test_discovery Catch2::Catch2)

add_subdirectory(bar)
add_subdirectory(foo)

add_executable(runner runner.cpp)
target_link_libraries(runner Catch2::Catch2)
# target_link_libraries(runner foo_tests)
# target_link_libraries(runner bar_tests)
