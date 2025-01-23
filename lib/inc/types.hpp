//
// Created by marijn on 1/7/25.
//

#ifndef CHESS_TYPES_HPP
#define CHESS_TYPES_HPP

#include <stdint.h>


#define _ND [[nodiscard]]


typedef enum {
	NONE =		0b000U,
	PAWN =		0b001U,
	KNIGHT =	0b010U,
	BISHOP =	0b011U,
	ROOK =		0b100U,
	QUEEN =		0b101U,
	KING =		0b110U,

	BLACK =		0b0000U,
	WHITE =		0b1000U
} piece_t;


#endif //CHESS_TYPES_HPP
