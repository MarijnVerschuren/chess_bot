//
// Created by marijn on 5/22/24.
//

#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP

#include <stdint.h>


typedef enum {
	NONE =		0b000U,
	PAWN =		0b001U,
	KNIGHT =	0b010U,
	BISHOP =	0b011U,
	ROOK =		0b100U,
	QUEEN =		0b101U,
	KING =		0b110U
} Chess_Piece;

typedef enum {
	BLACK =		0b0000U,
	WHITE =		0b1000U
} Chess_Color;


class Board {
public:
	Board();
	Board(Board& other);

	uint8_t operator[](uint8_t x, uint8_t y);

private:
	uint8_t board[32];
};


#endif //CHESS_BOARD_HPP
