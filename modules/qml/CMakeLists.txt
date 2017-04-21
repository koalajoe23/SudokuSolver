cmake_minimum_required(VERSION 3.0)
project(SudokuSolverQml)

include(../../common.cmake)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Qml REQUIRED)

FILE(GLOB_RECURSE HEADERS "include/*.h*")

add_library(${PROJECT_NAME}
    src/plugin.cpp
    src/cell.cpp
    src/board.cpp
    ${HEADERS} #needed for qt creator
    )

set(QML_DIR ${CMAKE_BINARY_DIR}/qml/SudokuSolver)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${QML_DIR}
)

message(STATUS "Generate qmldir file in ${QML_DIR}")
file(WRITE ${QML_DIR}/qmldir "module SudokuSolver\nplugin ${PROJECT_NAME}")

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Qml SudokuSolverCore)
