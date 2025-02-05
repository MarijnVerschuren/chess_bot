cmake_minimum_required(VERSION 3.27)
project(chess_bot C)

set(CMAKE_C_STANDARD 23)

include_directories(inc)
add_executable(chess_bot
    src/main.c
    src/board.c
    src/piece.c
    src/magic_const.c
    src/magic.c
    src/tree.c
    src/vector.c
)
