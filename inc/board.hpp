//
// Created by marijn on 1/23/25.
//

#ifndef CHESS_BOT_BOARD_HPP
#define CHESS_BOT_BOARD_HPP
#include "piece.hpp"



class Board {
public:
	Board();
	void init();

	uint32_t operator[](uint8_t row);

private:
	uint32_t rows[8];
};


typedef enum {
    SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1,
    SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2,
    SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3,
    SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4,
    SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5,
    SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6,
    SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7,
    SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8,
    SQ_NONE, SQ_CNT = 64
} square_t;


static const bit_board_t FILE_A = 0x0101010101010101ULL;
static const bit_board_t FILE_B = 0x0202020202020202ULL;
static const bit_board_t FILE_C = 0x0404040404040404ULL;
static const bit_board_t FILE_D = 0x0808080808080808ULL;
static const bit_board_t FILE_E = 0x1010101010101010ULL;
static const bit_board_t FILE_F = 0x2020202020202020ULL;
static const bit_board_t FILE_G = 0x4040404040404040ULL;
static const bit_board_t FILE_H = 0x8080808080808080ULL;

template<int8_t sft>
constexpr bit_board_t shift(bit_board_t board) {
	if constexpr (sft < 0)	{ return board >> (-sft); }
	else					{ return board << sft; }
}

template<color_t col>
constexpr sq_t rel_sq(sq_t sq) { return (sq_t)(sq ^ (col * 56)); }


#endif //CHESS_BOT_BOARD_HPP
