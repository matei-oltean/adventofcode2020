# Configuration

cmake_minimum_required(VERSION 3.1)

project("Advent2020")

# Compiler

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("utils/")

add_subdirectory("day01")
add_subdirectory("day03")
add_subdirectory("day04")
add_subdirectory("day05")
add_subdirectory("day06")
add_subdirectory("day07")
add_subdirectory("day08")
add_subdirectory("day10")
add_subdirectory("day11")
add_subdirectory("day12")