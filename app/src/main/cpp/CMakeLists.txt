cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

option(BUILD_SHARED_LIBS "Build shared library" on)
add_subdirectory(Catch2)
# target_link_libraries(Catch2 PRIVATE log)

project("unit_tests")

# add_subdirectory(static_modules)
add_subdirectory(shared_modules)

add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}
        # android
        # log
        Catch2::Catch2
        )
