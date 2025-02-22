#include <stdio.h>
#include <stdio.h>
#include <unistd.h>

#include "board.hpp"



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



uint64_t bishop_move_occupancy(uint64_t bb, const uint64_t occ) {
	uint64_t result = 0; for (;bb; bb &= (bb - 1)) {
		result |= index_magic_bishop(CTZ(bb), occ);
	} return result;
}

uint64_t rook_move_occupancy(uint64_t bb, const uint64_t occ) {
	uint64_t result = 0; for (;bb; bb &= (bb - 1)) {
		result |= index_magic_rook(CTZ(bb), occ);
	} return result;
}

uint64_t queen_move_occupancy(uint64_t bb, const uint64_t occ) {
	uint64_t result = 0; for (;bb; bb &= (bb - 1)) {
		result |= index_magic_queen(CTZ(bb), occ);
	} return result;
}



int main() {
	printf("%d", sizeof(Move));

	return 0;
}
