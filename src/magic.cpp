//
// Created by marijn on 2/1/25.
//

#include "magic.hpp"



bit_board_t index_magic_rook(sq_t sq, bit_board_t bb) {
	bb &= rook_blocker_mask[sq];
	return magic_rook_moves[
		rook_table_offset[sq] +\
		((rook_magics[sq] * bb) >> (SQ_CNT - rook_bits[sq]))
	];
}

bit_board_t index_magic_bishop(sq_t sq, bit_board_t bb) {
	bb &= bishop_blocker_mask[sq];
	return magic_bishop_moves[
		bishop_table_offset[sq] +\
		((bishop_magics[sq] * bb) >> (SQ_CNT - bishop_bits[sq]))
	];
}

bit_board_t index_magic_queen(sq_t sq, bit_board_t bb) {
	bit_board_t rbb = bb & rook_blocker_mask[sq];
	bit_board_t bbb = bb & bishop_blocker_mask[sq];
	return magic_rook_moves[
		rook_table_offset[sq] +\
		((rook_magics[sq] * rbb) >> (SQ_CNT - rook_bits[sq]))
	] | magic_bishop_moves[
		bishop_table_offset[sq] +\
		((bishop_magics[sq] * bbb) >> (SQ_CNT - bishop_bits[sq]))
	];
}
