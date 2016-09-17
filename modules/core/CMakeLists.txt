cmake_minimum_required(VERSION 3.0)
project(SudokuSolverCore)

include(../../common.cmake)

add_library(${PROJECT_NAME}
    src/cell.cpp
    src/board.cpp
    src/solver.cpp
    )

target_include_directories(${PROJECT_NAME} PUBLIC include)
