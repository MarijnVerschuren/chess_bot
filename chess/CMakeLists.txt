cmake_minimum_required(VERSION 3.27)
project(chess VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 23)

include_directories(/usr/local/include inc)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(PROJECT_SOURCE_DIR "src")
set(PROJECT_INCLUDE_DIR "inc")
set(PROJECT_TEST_DIR "test")
set(PROJECT_PY_BIND_DIR "src/py_bind")

set(SOURCE_FILES
    ${PROJECT_INCLUDE_DIR}/library.hpp
    ${PROJECT_SOURCE_DIR}/library.cpp
)

add_subdirectory(dep/pybind11)
add_library(chess_cpp SHARED ${SOURCE_FILES})
pybind11_add_module(chess_py ${SOURCE_FILES} ${PROJECT_PY_BIND_DIR}/py_bind.cpp)
add_executable(chess_test ${SOURCE_FILES} ${PROJECT_TEST_DIR}/main.cpp)
