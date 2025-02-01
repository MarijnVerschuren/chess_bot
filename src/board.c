//
// Created by marijn on 1/23/25.
//

#include "board.h"


void reset_board(board_t* board) {
	board->rows[0] = 0x00000000UL; board->rows[1] = 0x00000000UL;
	board->rows[2] = 0x00000000UL; board->rows[3] = 0x00000000UL;
	board->rows[4] = 0x00000000UL; board->rows[5] = 0x00000000UL;
	board->rows[6] = 0x00000000UL; board->rows[7] = 0x00000000UL;
}

void init_board(board_t* board) {
	board->rows[0] = (  // ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜
		((ROOK | WHITE) << 0x00)	| ((KNIGHT | WHITE) << 0x04)	|
		((BISHOP | WHITE) << 0x08)	| ((QUEEN | WHITE) << 0x0C)		|
		((KING | WHITE) << 0x10)	| ((BISHOP | WHITE) << 0x14)	|
		((KNIGHT | WHITE) << 0x18)	| ((ROOK | WHITE) << 0x1C)
	);
	board->rows[1] = (  // ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟
		((PAWN | WHITE) << 0x00)	| ((PAWN | WHITE) << 0x04)		|
		((PAWN | WHITE) << 0x08)	| ((PAWN | WHITE) << 0x0C)		|
		((PAWN | WHITE) << 0x10)	| ((PAWN | WHITE) << 0x14)		|
		((PAWN | WHITE) << 0x18)	| ((PAWN | WHITE) << 0x1C)
	);
	board->rows[2] = 0x00000000UL; board->rows[3] = 0x00000000UL;
	board->rows[4] = 0x00000000UL; board->rows[5] = 0x00000000UL;
	board->rows[6] = (  // ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟
		((PAWN | BLACK) << 0x00)	| ((PAWN | BLACK) << 0x04)		|
		((PAWN | BLACK) << 0x08)	| ((PAWN | BLACK) << 0x0C)		|
		((PAWN | BLACK) << 0x10)	| ((PAWN | BLACK) << 0x14)		|
		((PAWN | BLACK) << 0x18)	| ((PAWN | BLACK) << 0x1C)
	);
	board->rows[7] = (  // ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜
		((ROOK | BLACK) << 0x00)	| ((KNIGHT | BLACK) << 0x04)	|
		((BISHOP | BLACK) << 0x08)	| ((QUEEN | BLACK) << 0x0C)		|
		((KING | BLACK) << 0x10)	| ((BISHOP | BLACK) << 0x14)	|
		((KNIGHT | BLACK) << 0x18)	| ((ROOK | BLACK) << 0x1C)
	);
}


void reset_pbb(piece_bit_board_t* pbb) {
	pbb->board[BLACK | PAWN] =		0x0000000000000000ULL;
	pbb->board[BLACK | KNIGHT] =	0x0000000000000000ULL;
	pbb->board[BLACK | BISHOP] =	0x0000000000000000ULL;
	pbb->board[BLACK | ROOK] =		0x0000000000000000ULL;
	pbb->board[BLACK | QUEEN] =		0x0000000000000000ULL;
	pbb->board[BLACK | KING] =		0x0000000000000000ULL;

	pbb->board[WHITE | PAWN] =		0x0000000000000000ULL;
	pbb->board[WHITE | KNIGHT] =	0x0000000000000000ULL;
	pbb->board[WHITE | BISHOP] =	0x0000000000000000ULL;
	pbb->board[WHITE | ROOK] =		0x0000000000000000ULL;
	pbb->board[WHITE | QUEEN] =		0x0000000000000000ULL;
	pbb->board[WHITE | KING] =		0x0000000000000000ULL;
}

inline uint64_t pbb_occupancy(piece_bit_board_t* pbb, uint8_t color) {
	return (
		pbb->board[color | PAWN]	|
		pbb->board[color | KNIGHT]	|
		pbb->board[color | BISHOP]	|
		pbb->board[color | ROOK]	|
		pbb->board[color | QUEEN]	|
		pbb->board[color | KING]
	);
}


// TODO: move \/
const uint8_t bit_table[64] = {
	63, 30,  3, 32, 25, 41, 22, 33,
	15, 50, 42, 13, 11, 53, 19, 34,
	61, 29,  2,	51, 21, 43, 45, 10,
	18, 47,  1, 54,  9, 57,  0, 35,
	62, 31, 40,  4, 49,  5, 52,	26,
	60,  6, 23, 44, 46, 27, 56, 16,
	 7, 39, 48, 24, 59, 14, 12, 55,
	38, 28, 58, 20, 37, 17, 36,  8
};

uint8_t pop_bit(uint64_t *bb) {
	uint64_t b = *bb ^ (*bb - 1);
	uint32_t fold = ((b & 0xFFFFFFFFUL) ^ (b >> 32));
	*bb &= (*bb - 1);
	return bit_table[(fold * 0x783A9B23) >> 26];
}
// TODO: move ^


uint64_t bishop_move_occupancy(uint64_t bb, const uint64_t occ) {
	uint64_t result = 0; for (;bb;) {
		result |= index_magic_bishop(pop_bit(&bb), occ);
	} return result;
}

uint64_t rook_move_occupancy(uint64_t bb, const uint64_t occ) {
	uint64_t result = 0; for (;bb;) {
		result |= index_magic_rook(pop_bit(&bb), occ);
	} return result;
}

uint64_t queen_move_occupancy(uint64_t bb, const uint64_t occ) {
	uint64_t result = 0; for (;bb;) {
		result |= index_magic_queen(pop_bit(&bb), occ);
	} return result;
}


uint64_t pbb_move_occupancy(piece_bit_board_t* pbb, piece_bit_board_t* pmbb, uint8_t is_first_move) {
	uint64_t pbbb = pbb_occupancy(pbb, BLACK), pbbw = pbb_occupancy(pbb, WHITE);
	// PAWNs
	pmbb->board[BLACK | PAWN] = (
		((((pbb->board[BLACK | PAWN] & ~FILE_A) >> 7) | ((pbb->board[BLACK | PAWN] & ~FILE_H) >> 9)) & pbbw)	|
		(pbb->board[BLACK | PAWN] >> 8)	| (is_first_move * (pbb->board[BLACK | PAWN] >> 16))
	) & ~pbbb;
	pmbb->board[WHITE | PAWN] = (
		((((pbb->board[WHITE | PAWN] & ~FILE_H) << 7) | ((pbb->board[WHITE | PAWN] & ~FILE_A) << 9)) & pbbb)	|
		(pbb->board[WHITE | PAWN] << 8) | (is_first_move * (pbb->board[WHITE | PAWN] << 16))
	) & ~pbbw;
	// KNIGHTs
	pmbb->board[BLACK | KNIGHT] = (
		((pbb->board[BLACK | KNIGHT] & ~(FILE_A | FILE_B)) << 6)	|
		((pbb->board[BLACK | KNIGHT] & ~(FILE_A | FILE_B)) >> 10)	|
		((pbb->board[BLACK | KNIGHT] & ~(FILE_G | FILE_H)) >> 6)	|
		((pbb->board[BLACK | KNIGHT] & ~(FILE_G | FILE_H)) << 10)	|
		((pbb->board[BLACK | KNIGHT] & ~FILE_A) << 15)				|
		((pbb->board[BLACK | KNIGHT] & ~FILE_A) >> 17)				|
		((pbb->board[BLACK | KNIGHT] & ~FILE_H) >> 15)				|
		((pbb->board[BLACK | KNIGHT] & ~FILE_H) << 17)
	) & ~pbbb;
	pmbb->board[WHITE | KNIGHT] = (
		((pbb->board[WHITE | KNIGHT] & ~(FILE_A | FILE_B)) << 6)	|
		((pbb->board[WHITE | KNIGHT] & ~(FILE_A | FILE_B)) >> 10)	|
		((pbb->board[WHITE | KNIGHT] & ~(FILE_G | FILE_H)) >> 6)	|
		((pbb->board[WHITE | KNIGHT] & ~(FILE_G | FILE_H)) << 10)	|
		((pbb->board[WHITE | KNIGHT] & ~FILE_A) << 15)				|
		((pbb->board[WHITE | KNIGHT] & ~FILE_A) >> 17)				|
		((pbb->board[WHITE | KNIGHT] & ~FILE_H) >> 15)				|
		((pbb->board[WHITE | KNIGHT] & ~FILE_H) << 17)
	) & ~pbbw;
	// BISHOPs
	uint64_t obb = pbbb | pbbw;
	pmbb->board[BLACK | BISHOP] = bishop_move_occupancy(pbb->board[BLACK | BISHOP], obb) & ~pbbb;
	pmbb->board[WHITE | BISHOP] = bishop_move_occupancy(pbb->board[WHITE | BISHOP], obb) & ~pbbw;
	// ROOKs
	pmbb->board[BLACK | ROOK] = rook_move_occupancy(pbb->board[BLACK | ROOK], obb) & ~pbbb;
	pmbb->board[WHITE | ROOK] = rook_move_occupancy(pbb->board[WHITE | ROOK], obb) & ~pbbw;
	// QUEENs
	pmbb->board[BLACK | QUEEN] = queen_move_occupancy(pbb->board[BLACK | QUEEN], obb) & ~pbbb;
	pmbb->board[WHITE | QUEEN] = queen_move_occupancy(pbb->board[WHITE | QUEEN], obb) & ~pbbw;
	// KINGs
	pmbb->board[BLACK | KING] = king_moves[CTZ(pbb->board[BLACK | KING])] & ~pbbb;
	pmbb->board[WHITE | KING] = king_moves[CTZ(pbb->board[WHITE | KING])] & ~pbbw;

	// TODO: needed?
	return pbb_occupancy(pmbb, BLACK) | pbb_occupancy(pmbb, WHITE);
}


uint64_t calculate_pbb(board_t* board, piece_bit_board_t* pbb) {
	uint32_t tmp;
	uint64_t mask = 0b1;
	reset_pbb(pbb);
	for (uint8_t y = 0; y < 8; y++, mask <<= 8) {
		tmp = board->rows[y];
		for (uint8_t x = 0; x < 32; x += 4) {
			pbb->board[(tmp >> x) & 0xFU] |= mask << (x >> 2);
		}
	}
	// TODO: needed?
	return pbb_occupancy(pbb, BLACK) | pbb_occupancy(pbb, WHITE);
}






// TODO: remove (sample code for lookup)
bit_board_t k_table_lookup(bit_board_t board) {
	bit_board_t out = 0;
	for (uint8_t tz, index = 0; board; index += (tz + 1), board >>= (tz + 1)) {
		tz = CTZ(board);
		out |= king_moves[index + tz];
	}
	return out;
}