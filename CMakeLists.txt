cmake_minimum_required(VERSION 3.27)
project(chess_bot C)

set(CMAKE_C_STANDARD 23)

include_directories(inc)
add_executable(
    chess_bot
    src/main.c
    src/board.c
)
