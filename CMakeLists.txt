# Configuration

cmake_minimum_required(VERSION 3.1)

project("Advent2020")

# Compiler

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("utils/")

add_subdirectory("day01")
add_subdirectory("day04")
add_subdirectory("day05")