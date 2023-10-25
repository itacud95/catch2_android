cmake_minimum_required(VERSION 3.22.1)

project(foo)
add_executable(${PROJECT_NAME} foo.cpp)
target_link_libraries(${PROJECT_NAME} Catch2::Catch2WithMain)
