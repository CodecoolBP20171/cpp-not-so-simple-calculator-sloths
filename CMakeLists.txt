cmake_minimum_required(VERSION 3.8)
project(cpp_not_so_simple_calculator_sloths)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Tester.hpp main.cpp src/Calculator.cpp headers/Calculator.h src/ProblemPart.cpp headers/ProblemPart.h headers/PartType.h src/Parser.cpp headers/Parser.h)

add_executable(cpp_not_so_simple_calculator_sloths ${SOURCE_FILES})