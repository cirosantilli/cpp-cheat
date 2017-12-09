cmake_minimum_required(VERSION _3.0)
file(GLOB SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "*.c")
add_executable(main ${SOURCES})
