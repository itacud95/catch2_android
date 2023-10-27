cmake_minimum_required(VERSION 3.22.1)

project(modules)

add_subdirectory(bar)
add_subdirectory(foo)

add_executable(runner runner.cpp)
target_link_libraries(runner PUBLIC bar_tests foo_tests)
