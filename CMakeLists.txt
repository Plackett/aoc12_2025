cmake_minimum_required(VERSION 3.10)
project(aoc12_2025)

add_executable(aoc2025 main.cpp)
target_compile_features(aoc2025 PRIVATE cxx_std_17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ./build/x64/aoc.exe)