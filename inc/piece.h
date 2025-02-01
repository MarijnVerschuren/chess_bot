//
// Created by marijn on 1/24/25.
//

#ifndef CHESS_BOT_MOVE_H
#define CHESS_BOT_MOVE_H
#include "types.h"


typedef enum {
	NONE =		0b000U,
	PAWN =		0b001U,
	KNIGHT =	0b010U,
	BISHOP =	0b011U,
	ROOK =		0b100U,
	QUEEN =		0b101U,
	KING =		0b110U,

	ERROR =		0b111U,

	BLACK =		0b0000U,
	WHITE =		0b1000U
} piece_t;

extern const char* piece_names[16];

// king move lookup table
extern const bit_board_t king_moves[64];

#endif //CHESS_BOT_MOVE_H
