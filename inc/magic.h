//
// Created by marijn on 2/1/25.
//

#ifndef CHESS_BOT_MAGIC_H
#define CHESS_BOT_MAGIC_H
#include "types.h"


// move blocker masks
extern const uint64_t rook_blocker_mask[64];
extern const uint64_t bishop_blocker_mask[64];
// magic bit counts
extern const uint8_t rook_bits[64];
extern const uint8_t bishop_bits[64];
// magic numbers
extern const uint64_t rook_magics[64];
extern const uint64_t bishop_magics[64];
// square to move table offset
extern const uint32_t rook_table_offset[64];
extern const uint32_t bishop_table_offset[64];
// move tables indexed by magic
extern const uint64_t magic_rook_moves[102400];
extern const uint64_t magic_bishop_moves[5248];

// TODO: masks
uint64_t index_magic_rook(uint8_t sq, uint64_t bb);
uint64_t index_magic_bishop(uint8_t sq, uint64_t bb);
uint64_t index_magic_queen(uint8_t sq, uint64_t bb);

#endif //CHESS_BOT_MAGIC_H
