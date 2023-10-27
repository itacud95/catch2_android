cmake_minimum_required(VERSION 3.22.1)

project(foo)

add_library(foo_tests SHARED foo.cpp)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O0")
target_link_libraries(foo_tests test_discovery)
