//
// Created by marijn on 5/20/24.
//
#include <pybind11/pybind11.h>

#include "library.hpp"



PYBIND11_MODULE(chess, handle) {
	handle.doc() = "chess library";

	handle.def("hello", hello);
}