cmake_minimum_required(VERSION 3.20)
project(sudoku LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE PROJECT_SOURCES
     CONFIGURE_DEPENDS
     "${CMAKE_SOURCE_DIR}/src/*.cpp"
     "${CMAKE_SOURCE_DIR}/src/*.hpp"
     "${CMAKE_SOURCE_DIR}/src/*.h"
)

add_executable(sudoku ${PROJECT_SOURCES})

target_include_directories(sudoku PRIVATE "${CMAKE_SOURCE_DIR}/src")

target_compile_options(sudoku PRIVATE
    -Wall
    -Wextra
)

target_compile_definitions(sudoku PRIVATE
    $<$<CONFIG:Debug>:DEBUG;_DEBUG>
    $<$<CONFIG:Release>:RELEASE;NDEBUG>
)

target_compile_options(sudoku PRIVATE
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O3>
)
