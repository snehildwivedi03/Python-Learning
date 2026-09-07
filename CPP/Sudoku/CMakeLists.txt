cmake_minimum_required(VERSION 3.20)
project(Sudoku VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(Sanitizers.cmake)

add_executable(sudoku_app 
    main.cpp 
    board.cpp 
    engine.cpp 
    validator.cpp
)


target_include_directories(sudoku_app PRIVATE .)

enable_sanitizers(sudoku_app)