//
// Created by marijn on 5/22/24.
//

#include "board.hpp"


Board::Board() {
	this->board[0] = (  // ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜
		((ROOK | BLACK) << 0x00)	| ((KNIGHT | BLACK) << 0x04)	|
		((BISHOP | BLACK) << 0x08)	| ((QUEEN | BLACK) << 0x0C)		|
		((KING | BLACK) << 0x10)	| ((BISHOP | BLACK) << 0x14)	|
		((KNIGHT | BLACK) << 0x18)	| ((ROOK | BLACK) << 0x1C)
	);
	this->board[1] = (  // ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟
		((PAWN | BLACK) << 0x00)	| ((PAWN | BLACK) << 0x04)		|
		((PAWN | BLACK) << 0x08)	| ((PAWN | BLACK) << 0x0C)		|
		((PAWN | BLACK) << 0x10)	| ((PAWN | BLACK) << 0x14)		|
		((PAWN | BLACK) << 0x18)	| ((PAWN | BLACK) << 0x1C)
	);
	this->board[2] = 0x00000000UL; this->board[3] = 0x00000000UL;
	this->board[4] = 0x00000000UL; this->board[5] = 0x00000000UL;
	this->board[6] = (  // ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟
		((PAWN | WHITE) << 0x00)	| ((PAWN | WHITE) << 0x04)		|
		((PAWN | WHITE) << 0x08)	| ((PAWN | WHITE) << 0x0C)		|
		((PAWN | WHITE) << 0x10)	| ((PAWN | WHITE) << 0x14)		|
		((PAWN | WHITE) << 0x18)	| ((PAWN | WHITE) << 0x1C)
	);
	this->board[7] = (  // ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜
		((ROOK | WHITE) << 0x00)	| ((KNIGHT | WHITE) << 0x04)	|
		((BISHOP | WHITE) << 0x08)	| ((QUEEN | WHITE) << 0x0C)		|
		((KING | WHITE) << 0x10)	| ((BISHOP | WHITE) << 0x14)	|
		((KNIGHT | WHITE) << 0x18)	| ((ROOK | WHITE) << 0x1C)
	);
}

Board::Board(Board& other) {
	this->board[0] = other.board[0]; this->board[1] = other.board[1];
	this->board[2] = other.board[2]; this->board[3] = other.board[3];
	this->board[4] = other.board[4]; this->board[5] = other.board[5];
	this->board[6] = other.board[6]; this->board[7] = other.board[7];
}

uint8_t Board::operator[](uint8_t x, uint8_t y) {
	return (this->board[y] >> (x << 2)) & 0xF;
}

//uint8_t Board::move(uint8_t x, uint8_t y, uint8_t nx, uint8_t ny) {
//	x <<= 2; nx <<= 2;
//	uint8_t p = (this->board[y] >> x) & 0xF;
//	if (!p) { return -1; }		// no piece
//	this->board[y] &= ~(0xF << x);
//	if (this->board[ny] & (0xF << nx)) { return -2; }	// destination populated
//	this->board[ny] &= ~(0xF << nx);
//	this->board[ny] |= (p << nx);
//	return 0;
//}