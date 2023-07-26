cmake_minimum_required(VERSION 2.8.4)
project(hw1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(hw1
        Makefile
        solver.cpp)
