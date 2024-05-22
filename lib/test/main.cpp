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
			if (p & WHITE)	{ printf("WHITE "); }
			else			{ printf("BLACK "); }
			switch (p & 0b111) {
			case PAWN:		printf("PAWN\n");	break;
			case KNIGHT:	printf("KNIGHT\n");	break;
			case BISHOP:	printf("BISHOP\n");	break;
			case ROOK:		printf("ROOK\n");	break;
			case QUEEN:		printf("QUEEN\n");	break;
			case KING:		printf("KING\n");	break;
			}
		}
	}


	return 0;
}
