//
// Created by marijn on 12/24/24.
//

#include "move.hpp"


Move::Move(uint8_t src, uint8_t dst, move_t type, piece_t piece) {
	data = (
		((src & 0x3FU)				<< 0U)	|
		((dst & 0x3FU)				<< 6U)	|
		(((piece - KNIGHT) & 0x3U)	<< 12U)	|	// promotion piece
		((type & 0x3U) << 14U)					// move type
	);
}

uint16_t	Move::raw(void)						const	{ return data; }
uint8_t		Move::src(void)						const	{ return ((data >> 0U) & 0x3FU); }
uint8_t		Move::dst(void)						const	{ return ((data >> 6U) & 0x3FU); }
piece_t		Move::piece(void)					const	{ return (piece_t)(((data >> 12U) & 0x3U) + KNIGHT); }
move_t		Move::type(void)					const	{ return (move_t)((data >> 14U) & 0x3U); }

bool		Move::is_ok(void)					const	{ return data != 0 && data != 65; }

bool 		Move::operator==(const Move& move)	const	{ return data == move.data; }
bool 		Move::operator!=(const Move& move)	const	{ return data != move.data; }
			Move::operator bool(void)			const	{ return data != 0; }
			Move::operator uint16_t(void)		const	{ return data; }