#include <stdio.h>
#include <stdio.h>
#include <unistd.h>

#include "board.h"



/*!< print format
 * H1 H2 H3 H4 H5 H6 H7 H8
 * G1 G2 G3 G4 G5 G6 G7 G8
 * F1 F2 F3 F4 F5 F6 F7 F8
 * E1 E2 E3 E4 E5 E6 E7 E8
 * D1 D2 D3 D4 D5 D6 D7 D8
 * C1 C2 C3 C4 C5 C6 C7 C8
 * B1 B2 B3 B4 B5 B6 B7 B8
 * A1 A2 A3 A4 A5 A6 A7 A8
 */
void print_bb(uint64_t bb) {
	for (uint8_t y = 0; y < 8; y++) {
		for (uint8_t x = 0; x < 8; x++) {
			printf("%d ", (bb >> (63 - ((7 - x) + y * 8))) & 1);
		}
		printf("\n");
	}
	printf("\n\n");
}


void wip() {
	board_t board;
	piece_bit_board_t pbb;
	piece_bit_board_t mbb;

	init_board(&board);
	printf("occupancy:\n");
	print_bb(calculate_pbb(&board, &pbb));
	pbb_move_occupancy(&pbb, &mbb, 1);
	for (uint8_t i = 0; i < 16; i++) {
		if (!(i & 0x7U) || (i & 0x7U) == 0x7U) { continue; }
		printf("piece: %s(s):\n", piece_names[i]);
		printf("positions (%d):\n", CTZ(pbb.board[i]));
		print_bb(pbb.board[i]);
		printf("moves:\n");
		print_bb(mbb.board[i]);
	}
}


int main() {
	wip();

	return 0;
}
