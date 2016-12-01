cmake_minimum_required(VERSION 3.0)
project(SudokuSolverGui)

include(../../common.cmake)

function(files_from_qrc outvar file)
    get_filename_component(qrc_dir ${file} ABSOLUTE)
    get_filename_component(qrc_dir ${qrc_dir} DIRECTORY)
    file(STRINGS ${file} qrc_content)

    string(REGEX MATCHALL "<file[^<]*>[^<]*</file>" qrc_content ${qrc_content})
    string(REGEX REPLACE "<[^<]*>([^<]*)</[^<]*>" "${qrc_dir}/\\1;" qrc_files ${qrc_content})
    list(LENGTH qrc_files qrc_files_length)
    list(REMOVE_ITEM qrc_files "")

    message(STATUS "Found files in ${file}: ${qrc_files}")

    set(${outvar} ${qrc_files} PARENT_SCOPE)
endfunction(files_from_qrc)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Qml Widgets REQUIRED)

files_from_qrc(QML_FILES gui.qrc)
add_custom_target(qmlfiles SOURCES ${QML_FILES})
add_executable(${PROJECT_NAME} main.cpp gui.qrc)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Qml SudokuSolverCore)
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:QT_QML_DEBUG>)
