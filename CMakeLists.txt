cmake_minimum_required(VERSION 3.0)
project(SudokuSolver)

set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared lib? build static if unchecked")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)
message(STATUS "Generating ${CMAKE_BUILD_TYPE} Version of ${PROJECT_NAME}")

add_subdirectory(modules/core)
add_subdirectory(modules/cli)
add_subdirectory(modules/gui)
add_subdirectory(modules/qml)
