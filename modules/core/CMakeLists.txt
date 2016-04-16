cmake_minimum_required(VERSION 2.8)
project(${CMAKE_PROJECT_NAME}Core)

include(../../common.cmake)

set(SOURCE_FILES
    src/cell.cpp
    src/board.cpp
    )

set(HEADER_FILES
    include/sudokusolver/cell.hpp
    include/sudokusolver/board.hpp
    )
include_directories(include)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
add_library(${PROJECT_NAME}Static STATIC ${SOURCE_FILES} ${HEADER_FILES})

set_target_properties(${PROJECT_NAME}Static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

# Required on Unix OS family to be able to be linked into shared libraries.
set_target_properties(${PROJECT_NAME}Static PROPERTIES POSITION_INDEPENDENT_CODE ON)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
mark_as_advanced(${PROJECT_NAME}_INCLUDE_DIRS)
