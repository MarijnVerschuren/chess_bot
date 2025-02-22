//
// Created by marijn on 1/23/25.
//

#ifndef CHESS_BOT_BOARD_HPP
#define CHESS_BOT_BOARD_HPP
#include "piece.hpp"
#include "magic.hpp"
#include "move.hpp"



class Board {
public:
	Board();
	void init();

	uint32_t operator[](uint8_t row);

private:
	uint32_t rows[8];
};


static const bit_board_t FILE_A = 0x0101010101010101ULL;
static const bit_board_t FILE_B = 0x0202020202020202ULL;
static const bit_board_t FILE_C = 0x0404040404040404ULL;
static const bit_board_t FILE_D = 0x0808080808080808ULL;
static const bit_board_t FILE_E = 0x1010101010101010ULL;
static const bit_board_t FILE_F = 0x2020202020202020ULL;
static const bit_board_t FILE_G = 0x4040404040404040ULL;
static const bit_board_t FILE_H = 0x8080808080808080ULL;


#endif //CHESS_BOT_BOARD_HPP
