//
// Created by marijn on 2/1/25.
//

#ifndef CHESS_BOT_MAGIC_HPP
#define CHESS_BOT_MAGIC_HPP
#include "types.hpp"
#include "board.hpp"


// move blocker masks
extern const bit_board_t rook_blocker_mask[SQ_CNT];
extern const bit_board_t bishop_blocker_mask[SQ_CNT];
// magic bit counts
extern const uint8_t rook_bits[SQ_CNT];
extern const uint8_t bishop_bits[SQ_CNT];
// magic numbers
extern const bit_board_t rook_magics[SQ_CNT];
extern const bit_board_t bishop_magics[SQ_CNT];
// square to move table offset
extern const uint32_t rook_table_offset[SQ_CNT];
extern const uint32_t bishop_table_offset[SQ_CNT];
// move tables indexed by magic
extern const bit_board_t magic_rook_moves[102400];
extern const bit_board_t magic_bishop_moves[5248];


bit_board_t index_magic_rook(sq_t sq, bit_board_t bb);
bit_board_t index_magic_bishop(sq_t sq, bit_board_t bb);
bit_board_t index_magic_queen(sq_t sq, bit_board_t bb);


#endif //CHESS_BOT_MAGIC_HPP
