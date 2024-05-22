//
// Created by marijn on 5/20/24.
//
#include "chess.hpp"

#include "stdio.h"


Board board;
int main() {

	for (uint8_t y = 0; y < 8; y++) {
		for (uint8_t x = 0; x < 8; x++) {
			uint8_t p = board[x, y];
			if (!p) { continue; }
			if (p & WHITE)	{ printf("W"); }
			else			{ printf("B"); }
			switch (p & 0b111) {
			case PAWN:		printf("P ");	break;
			case KNIGHT:	printf("K ");	break;
			case BISHOP:	printf("B ");	break;
			case ROOK:		printf("R ");	break;
			case QUEEN:		printf("Q ");	break;
			case KING:		printf("K ");	break;
			}
		}
		printf("\n");
	}


	return 0;
}
