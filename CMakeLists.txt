cmake_minimum_required(VERSION 3.9)
project(greedy_grasp_ant C)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
add_executable(greedy_grasp_ant ${SOURCES} src/distributions.c src/distributions.h src/distances.c src/distances.h src/utils.c src/utils.h src/grasp.c src/grasp.h src/ant.c src/ant.h)
target_link_libraries(greedy_grasp_ant m)