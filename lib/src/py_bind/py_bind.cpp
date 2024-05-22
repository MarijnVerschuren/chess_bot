//
// Created by marijn on 5/20/24.
//
#include <pybind11/pybind11.h>

#include "board.hpp"
#include "chess.hpp"


namespace py = pybind11;


PYBIND11_MODULE(chess, handle) {
	handle.doc() = "chess library";


}