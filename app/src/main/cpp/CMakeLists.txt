cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

option(BUILD_SHARED_LIBS "Build shared library" on)
add_subdirectory(Catch2)
# target_link_libraries(Catch2 PRIVATE log)
target_link_libraries(Catch2 PRIVATE)

project("unit_tests")

add_subdirectory(modules/foo)
add_subdirectory(modules/bar)

add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}
        # android
        # log
        Catch2::Catch2
        )
