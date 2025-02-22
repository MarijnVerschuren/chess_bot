//
// Created by marijn on 2/4/25.
//

#ifndef CHESS_BOT_MOVE_HPP
#define CHESS_BOT_MOVE_HPP
#include "piece.hpp"



// move tables
extern const bit_board_t pawn_attacks[2][64];
extern const bit_board_t knight_attacks[64];
extern const bit_board_t pseudo_bishop_attacks[64];
extern const bit_board_t pseudo_rook_attacks[64];
extern const bit_board_t king_attacks[64];


typedef enum {
	MOVE =			0x0U,
	PROMOTION =		0x1U,
	EN_PASSANT =	0x2U,
	CASTLE =		0x3U
} move_t;


/*!< <H3>Move data structure</H3>
 * <P> 0:5 ->	src				</P>
 * <P> 6:11 ->	dst				</P>
 * <P> 12:13 ->	promotion piece	</P>
 * <P> 14:15 ->	move type		</P>
 */
class Move {
public:
	Move(uint8_t src, uint8_t dst, move_t type = MOVE, piece_t piece = KNIGHT);  // promotion piece
	Move(uint16_t move_data);

	_ND	uint16_t	raw(void)			const;
	_ND	uint8_t		src(void)			const;
	_ND	uint8_t		dst(void)			const;
	_ND	piece_t		piece(void)			const;
	_ND	move_t		type(void)			const;

	_ND	bool		is_ok(void)			const;

	bool operator==(const Move& move)	const;
	bool operator!=(const Move& move)	const;
	explicit operator bool(void)		const;
	explicit operator uint16_t(void)	const;

private:
	uint16_t data;
};


#endif //CHESS_BOT_MOVE_HPP
