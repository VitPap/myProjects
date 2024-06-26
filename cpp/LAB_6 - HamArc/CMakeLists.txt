cmake_minimum_required(VERSION 3.12)

project(labwork6  VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(lib)
add_subdirectory(Parser)

add_executable(labwork6 main.cpp lib/HamArc.cpp Parser/ArgParser.cpp Parser/Argument.cpp)

