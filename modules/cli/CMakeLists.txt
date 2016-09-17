cmake_minimum_required(VERSION 3.0)
project(SudokuSolverCli)

include(../../common.cmake)

add_executable(${PROJECT_NAME} main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME sudokusolver)
target_link_libraries(${PROJECT_NAME} PRIVATE SudokuSolverCore)
