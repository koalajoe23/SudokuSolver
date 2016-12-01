cmake_minimum_required(VERSION 3.0)
project(SudokuSolverQml)

include(../../common.cmake)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Qml REQUIRED)

#target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Qml)
