cmake_minimum_required(VERSION 3.20)

project(MapMaker C)
set(CMAKE_C_STANDARD 17)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_C_FLAGS "-Wall -Wextra -g")

link_directories(${CMAKE_SOURCE_DIR}/lib)
add_library(gdslib STATIC IMPORTED)
set_target_properties(gdslib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libgdslib.a)

add_executable(mapmaker mapmaker.c)
target_link_libraries(mapmaker gdslib raylib)
