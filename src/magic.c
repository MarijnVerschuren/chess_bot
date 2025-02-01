//
// Created by marijn on 2/1/25.
//

#include "magic.h"



uint64_t index_magic_rook(uint8_t sq, uint64_t bb) {
	bb &= rook_blocker_mask[sq];
	return magic_rook_moves[
		rook_table_offset[sq] +\
		((rook_magics[sq] * bb) >> (64 - rook_bits[sq]))
	];
}

uint64_t index_magic_bishop(uint8_t sq, uint64_t bb) {
	bb &= bishop_blocker_mask[sq];
	return magic_bishop_moves[
		bishop_table_offset[sq] +\
		((bishop_magics[sq] * bb) >> (64 - bishop_bits[sq]))
	];
}

uint64_t index_magic_queen(uint8_t sq, uint64_t bb) {
	uint64_t rbb = bb & rook_blocker_mask[sq];
	uint64_t bbb = bb & bishop_blocker_mask[sq];
	return magic_rook_moves[
		rook_table_offset[sq] +\
		((rook_magics[sq] * rbb) >> (64 - rook_bits[sq]))
	] | magic_bishop_moves[
		bishop_table_offset[sq] +\
		((bishop_magics[sq] * bbb) >> (64 - bishop_bits[sq]))
	];
}
