//
// Created by marijn on 2/27/25.
//

#include "search.hpp"
#include <cstring>



#include <stdio.h>
void print_mv(Move mv) {
	bit_board_t src = 0b1ULL << mv.src();
	bit_board_t dst = 0b1ULL << mv.dst();

	for (uint8_t y = 0; y < 8; y++) {
		for (uint8_t x = 0; x < 8; x++) {
			if ((src >> (63 - ((7 - x) + y * 8))) & 1) { printf("a "); continue; }
			if ((dst >> (63 - ((7 - x) + y * 8))) & 1) { printf("b "); continue; }
			printf("- ");
		}
		printf("\n");
	}
	printf("\n\n");
}


int32_t Search::search(Position& pos, uint8_t depth) {
	pos.print();

	Move move_list[MAX_MOVE];
	Move* end;
	Position wpos;

	end = generate(pos, move_list);
	for (Move* cur = move_list; cur != end; cur++) {
		memcpy(&wpos, &pos, sizeof(Position));
		wpos.move(*cur);
		search(pos, depth - 1);
	}

	return 0;
}