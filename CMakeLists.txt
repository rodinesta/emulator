cmake_minimum_required(VERSION 3.0)
project(emulator)

set(TINYXML2_DIR ${CMAKE_SOURCE_DIR}/CMakeInclude/tinyxml2)

include_directories(${TINYXML2_DIR})

link_directories(${TINYXML2_DIR})

add_executable(emulator main.cpp)

target_link_libraries(emulator tinyxml2)