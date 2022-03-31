cmake_minimum_required(VERSION 3.16)
project(ASD-L1-Complexite)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

add_executable(L1-test complexity.h sort_functions.h main_test.cpp
        op_counter.h op_counter.cpp)
add_executable(L1-time complexity.h sort_functions.h main_time.cpp
        op_counter.h op_counter.cpp)
add_executable(L1-operations complexity.h sort_functions.h
        main_operations.cpp op_counter.h op_counter.cpp)