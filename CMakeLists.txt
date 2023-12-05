cmake_minimum_required(VERSION 3.0)
project(emulator)

set(TINYXML2_DIR ${CMAKE_SOURCE_DIR}/CMakeInclude/tinyxml2)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeInclude)

find_package(Libevent REQUIRED)

include_directories(${TINYXML2_DIR} ${Libevent_INCLUDE_DIRS})

link_directories(${TINYXML2_DIR} ${Libevent_LIBRARY_DIRS})

add_executable(emulator 
    main.cpp 
    server.cpp 
    modbus_unit.cpp)

target_link_libraries(emulator tinyxml2 ${Libevent_LIBRARIES})