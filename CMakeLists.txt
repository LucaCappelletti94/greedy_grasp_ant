cmake_minimum_required(VERSION 3.13)
project(greedy_grasp_ant C)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
add_executable(greedy_grasp_ant ${SOURCES})
