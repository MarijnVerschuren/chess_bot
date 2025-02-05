//
// Created by marijn on 1/23/25.
//

#include "board.h"
#include "move.h"


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


static piece_bit_board_t bb;	// position bb
void generate_moves(tree_t* tree, board_t* board, uint8_t is_first_move) {
	calculate_pbb(board, &bb);

	// TODO
	uint64_t tmpbb;
	move_t move;

	for(;bb.board[BLACK | PAWN]; bb.board[BLACK | PAWN] &= bb.board[BLACK | PAWN] - 1) {
		move.src = CTZ(bb.board[BLACK | PAWN]);
		tmpbb = 0;  // TODO: lookups!

		for (;tmpbb; tmpbb &= tmpbb - 1) {
			move.dst = CTZ(tmpbb);

		}
	}
}


void calculate_pbb(board_t* board, piece_bit_board_t* pbb) {
	uint32_t tmp;
	uint64_t mask = 0b1;
	reset_pbb(pbb);
	for (uint8_t y = 0; y < 8; y++, mask <<= 8) {
		tmp = board->rows[y];
		for (uint8_t x = 0; x < 32; x += 4) {
			pbb->board[(tmp >> x) & 0xFU] |= mask << (x >> 2);
		}
	}

	pbb->board[ALL | BLACK] = (
		pbb->board[BLACK | PAWN]	|
		pbb->board[BLACK | KNIGHT]	|
		pbb->board[BLACK | BISHOP]	|
		pbb->board[BLACK | ROOK]	|
		pbb->board[BLACK | QUEEN]	|
		pbb->board[BLACK | KING]
	);
	pbb->board[ALL | WHITE] = (
		pbb->board[WHITE | PAWN]	|
		pbb->board[WHITE | KNIGHT]	|
		pbb->board[WHITE | BISHOP]	|
		pbb->board[WHITE | ROOK]	|
		pbb->board[WHITE | QUEEN]	|
		pbb->board[WHITE | KING]
	);
}


/*
void pbb_move_occupancy(piece_bit_board_t* pbb, piece_bit_board_t* pmbb, uint8_t is_first_move) {
	// PAWNs
	pmbb->board[BLACK | PAWN] = (
		((((pbb->board[BLACK | PAWN] & ~FILE_A) >> 7) | ((pbb->board[BLACK | PAWN] & ~FILE_H) >> 9)) & pbb->board[ALL | WHITE])	|
		(pbb->board[BLACK | PAWN] >> 8)	| (is_first_move * (pbb->board[BLACK | PAWN] >> 16))
	) & ~pbb->board[ALL | BLACK];
	pmbb->board[WHITE | PAWN] = (
		((((pbb->board[WHITE | PAWN] & ~FILE_H) << 7) | ((pbb->board[WHITE | PAWN] & ~FILE_A) << 9)) & pbb->board[ALL | BLACK])	|
		(pbb->board[WHITE | PAWN] << 8) | (is_first_move * (pbb->board[WHITE | PAWN] << 16))
	) & ~pbb->board[ALL | WHITE];
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
	) & ~pbb->board[ALL | BLACK];
	pmbb->board[WHITE | KNIGHT] = (
		((pbb->board[WHITE | KNIGHT] & ~(FILE_A | FILE_B)) << 6)	|
		((pbb->board[WHITE | KNIGHT] & ~(FILE_A | FILE_B)) >> 10)	|
		((pbb->board[WHITE | KNIGHT] & ~(FILE_G | FILE_H)) >> 6)	|
		((pbb->board[WHITE | KNIGHT] & ~(FILE_G | FILE_H)) << 10)	|
		((pbb->board[WHITE | KNIGHT] & ~FILE_A) << 15)				|
		((pbb->board[WHITE | KNIGHT] & ~FILE_A) >> 17)				|
		((pbb->board[WHITE | KNIGHT] & ~FILE_H) >> 15)				|
		((pbb->board[WHITE | KNIGHT] & ~FILE_H) << 17)
	) & ~pbb->board[ALL | WHITE];
	// BISHOPs
	uint64_t obb = pbb->board[ALL | BLACK] | pbb->board[ALL | WHITE];
	pmbb->board[BLACK | BISHOP] = bishop_move_occupancy(pbb->board[BLACK | BISHOP], obb) & ~pbb->board[ALL | BLACK];
	pmbb->board[WHITE | BISHOP] = bishop_move_occupancy(pbb->board[WHITE | BISHOP], obb) & ~pbb->board[ALL | WHITE];
	// ROOKs
	pmbb->board[BLACK | ROOK] = rook_move_occupancy(pbb->board[BLACK | ROOK], obb) & ~pbb->board[ALL | BLACK];
	pmbb->board[WHITE | ROOK] = rook_move_occupancy(pbb->board[WHITE | ROOK], obb) & ~pbb->board[ALL | WHITE];
	// QUEENs
	pmbb->board[BLACK | QUEEN] = queen_move_occupancy(pbb->board[BLACK | QUEEN], obb) & ~pbb->board[ALL | BLACK];
	pmbb->board[WHITE | QUEEN] = queen_move_occupancy(pbb->board[WHITE | QUEEN], obb) & ~pbb->board[ALL | WHITE];
	// KINGs
	pmbb->board[BLACK | KING] = king_moves[CTZ(pbb->board[BLACK | KING])] & ~pbb->board[ALL | BLACK];
	pmbb->board[WHITE | KING] = king_moves[CTZ(pbb->board[WHITE | KING])] & ~pbb->board[ALL | WHITE];
}
*/