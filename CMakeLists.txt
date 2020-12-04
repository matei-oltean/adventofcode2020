# Configuration

cmake_minimum_required(VERSION 3.1)

project("Advent2020")

# Compiler

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -s")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("utils/")

add_subdirectory("day01")
add_subdirectory("day04")