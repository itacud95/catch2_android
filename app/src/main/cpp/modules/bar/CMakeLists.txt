cmake_minimum_required(VERSION 3.22.1)

project(bar)
add_executable(${PROJECT_NAME} bar.cpp)
target_link_libraries(${PROJECT_NAME} Catch2::Catch2WithMain)
