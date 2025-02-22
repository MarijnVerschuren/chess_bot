//
// Created by marijn on 1/23/25.
//

#include "board.hpp"
#include "move.hpp"



Board::Board() {
	rows[0] = 0x00000000UL; rows[1] = 0x00000000UL;
	rows[2] = 0x00000000UL; rows[3] = 0x00000000UL;
	rows[4] = 0x00000000UL; rows[5] = 0x00000000UL;
	rows[6] = 0x00000000UL; rows[7] = 0x00000000UL;
}

void Board::init() {
	rows[0] = (  // ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜
		((ROOK | WHT) << 0x00)		| ((KNIGHT | WHT) << 0x04)	|
		((BISHOP | WHT) << 0x08)	| ((QUEEN | WHT) << 0x0C)	|
		((KING | WHT) << 0x10)		| ((BISHOP | WHT) << 0x14)	|
		((KNIGHT | WHT) << 0x18)	| ((ROOK | WHT) << 0x1C)
	);
	rows[1] = (  // ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟
		((PAWN | WHT) << 0x00)		| ((PAWN | WHT) << 0x04)	|
		((PAWN | WHT) << 0x08)		| ((PAWN | WHT) << 0x0C)	|
		((PAWN | WHT) << 0x10)		| ((PAWN | WHT) << 0x14)	|
		((PAWN | WHT) << 0x18)		| ((PAWN | WHT) << 0x1C)
	);
	rows[2] = 0x00000000UL; rows[3] = 0x00000000UL;
	rows[4] = 0x00000000UL; rows[5] = 0x00000000UL;
	rows[6] = (  // ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟
		((PAWN | BLK) << 0x00)		| ((PAWN | BLK) << 0x04)	|
		((PAWN | BLK) << 0x08)		| ((PAWN | BLK) << 0x0C)	|
		((PAWN | BLK) << 0x10)		| ((PAWN | BLK) << 0x14)	|
		((PAWN | BLK) << 0x18)		| ((PAWN | BLK) << 0x1C)
	);
	rows[7] = (  // ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜
		((ROOK | BLK) << 0x00)		| ((KNIGHT | BLK) << 0x04)	|
		((BISHOP | BLK) << 0x08)	| ((QUEEN | BLK) << 0x0C)	|
		((KING | BLK) << 0x10)		| ((BISHOP | BLK) << 0x14)	|
		((KNIGHT | BLK) << 0x18)	| ((ROOK | BLK) << 0x1C)
	);
}

uint32_t Board::operator[](uint8_t row) { return this->rows[row]; }
