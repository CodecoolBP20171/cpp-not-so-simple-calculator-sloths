cmake_minimum_required(VERSION 3.8)
project(cpp_not_so_simple_calculator_sloths)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Tester.hpp main.cpp Calculator.cpp Calculator.h ProblemPart.cpp ProblemPart.h PartType.h Parser.cpp Parser.h)

add_executable(cpp_not_so_simple_calculator_sloths ${SOURCE_FILES})