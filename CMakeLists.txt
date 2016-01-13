cmake_minimum_required(VERSION 2.6)
enable_testing()
project(cgmd)
set(CGMD_VERSION_MAJOR 0)
set(CGMD_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS -Wall)
add_definitions("-std=c++11")

include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(samples)
