cmake_minimum_required(VERSION 3.0)
project(SudokuSolverCore)

include(../../common.cmake)

FILE(GLOB_RECURSE HEADERS "include/*.h*")

add_library(${PROJECT_NAME}
    src/cell.cpp
    src/board.cpp
    src/solver.cpp
    src/board_observer.cpp
    ${HEADERS} #needed for qt creator
    )


target_include_directories(${PROJECT_NAME} PUBLIC include)
