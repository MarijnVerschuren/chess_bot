//
// Created by marijn on 1/24/25.
//

#ifndef CHESS_BOT_PIECE_HPP
#define CHESS_BOT_PIECE_HPP
#include "misc.hpp"



typedef enum : uint8_t {
	NONE =		0b000U,
	PAWN =		0b001U,
	KNIGHT =	0b010U,
	BISHOP =	0b011U,
	ROOK =		0b100U,
	QUEEN =		0b101U,
	KING =		0b110U,

	ALL =		0b111U,		// all pieces index
	COL =		0b1000U,	// color mask

	WHT =		0b0000U,	// white, all WHITE pieces index
	BLK =		0b1000U		// black
} piece_t;

enum color_t : uint8_t {
	WHITE =		0b0U,
	BLACK =		0b1U,
	COL_CNT =	0b10U,
};


constexpr piece_t mk_piece(color_t c, piece_t p)	{ return (piece_t)(((!c) << 3) | p); }
constexpr piece_t operator+(piece_t a, piece_t b)	{ return (piece_t)((uint8_t)a + (uint8_t)b); }
constexpr color_t operator!(color_t color)			{ return (color_t)(color ^ 0b1U); }
constexpr int8_t pawn_push(color_t color)			{ return (int8_t)(8 * (1 - (color << 1))); }

extern const char* piece_names[16];


#endif //CHESS_BOT_PIECE_HPP
