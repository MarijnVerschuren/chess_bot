//
// Created by marijn on 5/22/24.
//

#include "board.hpp"


Board::Board() {
	// TODO: default board state
}

Board::Board(Board& other) {
	// TODO: copy board state from other
}

uint8_t Board::operator[](uint8_t x, uint8_t y) {
	return (this->board[y * 4 + (x >> 1)] >> (4 * (x & 0b1))) & 0xF;
}
