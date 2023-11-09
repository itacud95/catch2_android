cmake_minimum_required(VERSION 3.22.1)

project("unit_tests")

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CATCH_CONFIG_ANDROID_LOGWRITE on)

option(CATCH_CONFIG_ANDROID_LOGWRITE "Android logging" on)
option(BUILD_SHARED_LIBS "Build shared library" on)

add_subdirectory(Catch2)
if(CMAKE_SYSTEM_NAME MATCHES "Android")
    target_link_libraries(Catch2 PRIVATE log)
endif()
 

add_subdirectory(shared_modules)

add_library(${CMAKE_PROJECT_NAME} SHARED
    native-lib.cpp)

if(CMAKE_SYSTEM_NAME MATCHES "Android")
    set(android_libs android log)
endif()

target_link_libraries(${CMAKE_PROJECT_NAME}
    ${android_libs}
    Catch2::Catch2
)

add_executable(main main.cpp)
target_link_libraries(main ${PROJECT_NAME})