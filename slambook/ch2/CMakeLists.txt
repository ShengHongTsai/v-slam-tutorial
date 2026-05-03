cmake_minimum_required(VERSION 2.8)

project(hello_slam)

add_library(lib_hello_slam lib_hello_slam.cpp)
add_library(shared_hello_slam SHARED lib_hello_slam.cpp)

add_executable(use_hello_slam hello_slam.cpp)
target_link_libraries(use_hello_slam shared_hello_slam)