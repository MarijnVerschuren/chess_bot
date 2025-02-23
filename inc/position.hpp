//
// Created by marijn on 2/5/25.
//

#ifndef CHESS_BOT_POSITION_HPP
#define CHESS_BOT_POSITION_HPP
#include "board.hpp"
#include "move.hpp"
#include "magic.hpp"



typedef enum {
	WHITE_KING_SIDE =	0b0001U,
	WHITE_QUEEN_SIDE =	0b0010U,
	BLACK_KING_SIDE =	0b0100U,
	BLACK_QUEEN_SIDE =	0b1000U,

	KING_SIDE =			WHITE_KING_SIDE | BLACK_KING_SIDE,
	QUEEN_SIDE =		WHITE_QUEEN_SIDE | BLACK_QUEEN_SIDE,
	WHITE_CASTLING =	WHITE_KING_SIDE | WHITE_QUEEN_SIDE,
	BLACK_CASTLING =	BLACK_KING_SIDE | BLACK_QUEEN_SIDE,
	ANY_CASTLING =		WHITE_CASTLING | BLACK_CASTLING,

	CASTLE_CNT = 4
} castle_t;

constexpr castle_t operator&(castle_t a, castle_t b)		{ return (castle_t)(((uint8_t)a) & ((uint8_t)b)); }
constexpr castle_t operator&(color_t col, castle_t castle)	{ return (col == WHITE ? WHITE_CASTLING : BLACK_CASTLING) & castle; }

extern const sq_t castle_ksq[CASTLE_CNT];
extern const sq_t castle_rsq[CASTLE_CNT];
extern const bit_board_t castle_masks[CASTLE_CNT];
extern const bit_board_t line_bb[SQ_CNT][SQ_CNT];
extern const bit_board_t between_bb[SQ_CNT][SQ_CNT];


class Position {
public:
	// initialization
	Position() = default;
	Position(Board& board, color_t stm, uint8_t castle);
	void update_slider_blockers(color_t color);

	// board functions
	_ND	bit_board_t piece(piece_t piece)					const;
	_ND	bit_board_t piece(color_t color, piece_t piece)		const;
	_ND	bit_board_t attackers_to(sq_t sq, color_t color)	const;
	_ND	bit_board_t attackers_to(sq_t sq)					const;

	// move functions
	_ND bool legal(const Move move)							const;

	// getters
	_ND	bit_board_t king_blockers_g(color_t color)			const;
	_ND	bit_board_t checkers_g(void)						const;
	_ND	color_t side_to_move_g(void)						const;
	_ND	sq_t en_passant_sq_g(void)							const;
	// castling
	_ND castle_t can_castle(castle_t castle)				const;
	_ND bool castle_impeded(castle_t castle)				const;
	_ND sq_t castling_rook_square(castle_t castle)			const;
	_ND sq_t castling_king_square(castle_t castle)			const;


	bit_board_t* psc() { return this->pieces; }

private:
	Board		board;

	// 0: WHITE pieces
	// 1 - 6: PAWNS - KINGS
	// 7: ALL pieces
	// 8: BLACK pieces
    bit_board_t	pieces[9];

	bit_board_t checkers;
	bit_board_t	king_blockers[COL_CNT];
	bit_board_t	pinners[COL_CNT];

	color_t 	side_to_move	: 1;
	castle_t	castle_rights	: 4;  // TODO

	sq_t		en_passant_sq;	// TODO: use!
};



#endif //CHESS_BOT_POSITION_HPP
