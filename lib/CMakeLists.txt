cmake_minimum_required(VERSION 3.27)
project(chess VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 23)

include_directories(/usr/local/include inc)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(PROJECT_SOURCE_DIR "src")
set(PROJECT_INCLUDE_DIR "inc")
set(PROJECT_TEST_DIR "test")
set(PROJECT_PY_BIND_DIR "src/py_bind")

set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/tree.cpp
    ${PROJECT_SOURCE_DIR}/board.cpp
    ${PROJECT_SOURCE_DIR}/move.cpp
    ${PROJECT_SOURCE_DIR}/chess.cpp
)

# chess_py
add_subdirectory(dep/pybind11)
pybind11_add_module(chess_py ${SOURCE_FILES} ${PROJECT_PY_BIND_DIR}/py_bind.cpp)
# chess_cpp
add_library(chess_cpp SHARED ${SOURCE_FILES})
# chess_test
add_executable(chess_test ${SOURCE_FILES} ${PROJECT_TEST_DIR}/main.cpp)
