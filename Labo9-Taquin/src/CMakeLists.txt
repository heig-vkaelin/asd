cmake_minimum_required(VERSION 3.17)
project(ASD_Labo9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

add_executable(L9 main.cpp vertex.cpp vertex.h graph.cpp graph.h)
