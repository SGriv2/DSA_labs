cmake_minimum_required(VERSION 3.2)

project(lab3)

add_executable(main main.cpp)

add_library(fib fibbonachi.hpp fibbonachi_viz.hpp)

set_target_properties(fib PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(main PRIVATE fib)
