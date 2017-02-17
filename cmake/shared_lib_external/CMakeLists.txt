cmake_minimum_required(VERSION 2.8)
add_executable(main main.c)
target_link_libraries(main gsl gslcblas)
