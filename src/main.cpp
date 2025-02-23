#include <stdio.h>
#include <stdio.h>
#include <unistd.h>

#include "position.hpp"
#include "move_gen.hpp"



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
void print_bb(bit_board_t bb) {
	for (uint8_t y = 0; y < 8; y++) {
		for (uint8_t x = 0; x < 8; x++) {
			printf("%d ", (bb >> (63 - ((7 - x) + y * 8))) & 1);
		}
		printf("\n");
	}
	printf("\n\n");
}

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



Move move_list[MAX_MOVE];

int main() {
	Board board;
	board.init();

	Position pos(board, WHITE, ANY_CASTLING);  // TODO: FEN
	Move* end = generate(pos, move_list);

	for (Move* cur = move_list; cur != end; cur++) {
		print_mv(*cur);
	}

	return 0;
}
