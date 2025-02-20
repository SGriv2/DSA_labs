cmake_minimum_required(VERSION 3.2)

project(lab2)

add_executable(main main.cpp)

add_library(h_files hashtab.hpp preftree.hpp rbtree.hpp)

set_target_properties(h_files PROPERTIES LINKER_LANGUAGE CXX)

add_library(cpp_files preftree.cpp rbtree.cpp hashtab.cpp)

target_link_libraries(cpp_files PRIVATE h_files)
target_link_libraries(main PRIVATE cpp_files)