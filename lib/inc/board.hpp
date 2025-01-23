//
// Created by marijn on 5/22/24.
//

#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP

#include "move.hpp"


class Board {
public:
	Board();
	Board(Board& other);
	// TODO: from standard string (UCI)

	uint8_t operator[](uint8_t x, uint8_t y);

	//uint8_t move(uint8_t x, uint8_t y, uint8_t nx, uint8_t ny);
	// TODO: other move formats? (UCI)

protected:
	uint32_t board[8];
};



#endif //CHESS_BOARD_HPP
