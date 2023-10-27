cmake_minimum_required(VERSION 3.22.1)

project(modules)

add_link_options(--no-gnu-unique)
add_compile_options(-fPIC)
add_compile_options(-ggdb3)
add_compile_options(-O0)

add_library(test_discovery OBJECT test_discovery.cpp)
target_link_libraries(test_discovery Catch2::Catch2)

add_subdirectory(bar)
add_subdirectory(foo)

add_executable(runner runner.cpp)
target_link_libraries(runner Catch2::Catch2WithMain)
