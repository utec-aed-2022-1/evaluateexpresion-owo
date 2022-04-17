cmake_minimum_required(VERSION 3.17)
project(evaluateexpresion_owo)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(evaluateexpresion_owo
        list.h
        main.cpp
        solution.h
        tester.h)
