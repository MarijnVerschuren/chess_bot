cmake_minimum_required(VERSION 3.27)
project(chess_bot C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

include_directories(inc)
add_executable(chess_bot
    src/main.cpp
    src/board.cpp
    src/piece.cpp
    src/magic_const.cpp
    src/move_gen.cpp
    src/magic.cpp
    src/position.cpp
    src/move.cpp
)
