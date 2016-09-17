cmake_minimum_required(VERSION 3.0)
project(SudokuSolver)

set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared lib? build static if unchecked")

add_subdirectory(modules/core)
add_subdirectory(modules/cli)
