cmake_minimum_required(VERSION 2.8)
project(${CMAKE_PROJECT_NAME}Cli)

include(../../common.cmake)

include_directories(${${CMAKE_PROJECT_NAME}Core_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME sudokusolver)
target_link_libraries(${PROJECT_NAME} ${CMAKE_PROJECT_NAME}Core.a)
