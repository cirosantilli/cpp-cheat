cmake_minimum_required(VERSION 3.0)
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
add_executable(main ${SOURCES})
