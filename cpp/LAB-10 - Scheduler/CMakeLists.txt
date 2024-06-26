cmake_minimum_required(VERSION 3.12)

project(
        labwork10
        VERSION 1.0
        DESCRIPTION "Labwork10"
        LANGUAGES CXX
)


set(CMAKE_CXX_STANDARD 20)

enable_testing()
add_subdirectory(tests)