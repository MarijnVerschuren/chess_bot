//
// Created by marijn on 1/23/25.
//

#ifndef CHESS_BOT_BOARD_H
#define CHESS_BOT_BOARD_H
#include "piece.h"
#include "magic.h"


typedef struct {
	uint32_t rows[8];
} board_t;

typedef struct {
	uint64_t board[16];
} piece_bit_board_t;


static const bit_board_t FILE_A = 0x0101010101010101ULL;
static const bit_board_t FILE_B = 0x0202020202020202ULL;
static const bit_board_t FILE_C = 0x0404040404040404ULL;
static const bit_board_t FILE_D = 0x0808080808080808ULL;
static const bit_board_t FILE_E = 0x1010101010101010ULL;
static const bit_board_t FILE_F = 0x2020202020202020ULL;
static const bit_board_t FILE_G = 0x4040404040404040ULL;
static const bit_board_t FILE_H = 0x8080808080808080ULL;


/*<!
 * board
 * */
void reset_board(board_t* board);
void init_board(board_t* board);

/*<!
 * piece bit board (pbb)
 * */
void reset_pbb(piece_bit_board_t* pbb);
// returns the bit board occupancy (all pieces of a certain color)
bit_board_t pbb_occupancy(piece_bit_board_t* pbb, uint8_t color);
// returns the full move bit board and stores the piece move bit boards in pmbb
bit_board_t pbb_move_occupancy(piece_bit_board_t* pbb, piece_bit_board_t* pmbb, uint8_t is_first_move);

bit_board_t calculate_pbb(board_t* board, piece_bit_board_t* pbb);



#endif //CHESS_BOT_BOARD_H
