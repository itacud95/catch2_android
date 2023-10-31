cmake_minimum_required(VERSION 3.22.1)

project("unit_tests")

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O0")

# set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS} -rdynamic")
# set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -rdynamic")
# set(CMAKE_CXX_FLAGS -rdynamic)

option(BUILD_SHARED_LIBS "Build shared library" on)
add_subdirectory(Catch2)
if(CMAKE_SYSTEM_NAME MATCHES "Android")
target_link_libraries(Catch2 PRIVATE log)
endif()


# add_subdirectory(static_modules)
add_subdirectory(shared_modules)

add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp)

if(CMAKE_SYSTEM_NAME MATCHES "Android")
set(android_libs android log)
endif()

target_link_libraries(${CMAKE_PROJECT_NAME}
        ${android_libs}
        foo_tests
        bar_tests
        Catch2::Catch2
        )
