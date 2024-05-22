//
// Created by marijn on 5/20/24.
//
#include <pybind11/pybind11.h>

#include "board.hpp"
#include "chess.hpp"


namespace py = pybind11;


PYBIND11_MODULE(chess, handle) {
	handle.doc() = "chess library";

	/*<!
	 * board.hpp
	 * */
	// Chess_Piece
	py::enum_<Chess_Piece> chess_piece(handle, "Chess_Piece");
	chess_piece.value("NONE",	Chess_Piece::NONE);
	chess_piece.value("PAWN",	Chess_Piece::PAWN);
	chess_piece.value("KNIGHT",	Chess_Piece::KNIGHT);
	chess_piece.value("BISHOP",	Chess_Piece::BISHOP);
	chess_piece.value("ROOK",	Chess_Piece::ROOK);
	chess_piece.value("QUEEN",	Chess_Piece::QUEEN);
	chess_piece.value("KING",	Chess_Piece::KING);
	chess_piece.export_values();

	// Chess_Color
	py::enum_<Chess_Color> chess_color(handle, "Chess_Color");
	chess_color.value("BLACK",	Chess_Color::BLACK);
	chess_color.value("WHITE",	Chess_Color::WHITE);
	chess_color.export_values();

	// Board
	py::class_<Board> board(handle, "Board");
	board.def(py::init<>());
	board.def(py::init<Board&>());
	board.def("__getitem__", [](Board* self, std::tuple<uint8_t, uint8_t> pos) {
		return self->operator[](std::get<0>(pos), std::get<1>(pos));
	});

}