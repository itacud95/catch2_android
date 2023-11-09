cmake_minimum_required(VERSION 3.22.1)

project("unit_tests")

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(${CMAKE_PROJECT_NAME} SHARED
    native-lib.cpp)

if(CMAKE_SYSTEM_NAME MATCHES "Android")
    set(android_libs android log)
endif()

target_link_libraries(${CMAKE_PROJECT_NAME}
    android
    log
)
