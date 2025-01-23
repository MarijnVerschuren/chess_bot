//
// Created by marijn on 12/24/24.
//

#ifndef CHESS_MOVE_HPP
#define CHESS_MOVE_HPP

#include "types.hpp"


typedef enum {
	MOVE =			0x0U,
	PROMOTION =		0x1U,
	EN_PASSANT =	0x2U,
	CASTLE =		0x3U
} move_t;

/*!< <H3>Move data structure</H3>
 * <P> 0:5&emsp;->	src				</P>
 * <P> 6:11&emsp;->	dst				</P>
 * <P> 12:13&ensp;->	promotion piece	</P>
 * <P> 14:15&ensp;->	move type		</P>
 */
class Move {
public:
	Move(uint8_t src, uint8_t dst, move_t type = MOVE, piece_t piece = KNIGHT);  // promotion piece
	Move(uint16_t move_data) : data(move_data) {};

	_ND	uint16_t	raw(void)			const;
	_ND	uint8_t		src(void)			const;
	_ND	uint8_t		dst(void)			const;
	_ND	piece_t		piece(void)			const;
	_ND	move_t		type(void)			const;

	_ND	bool		is_ok(void)			const;  // TODO: needed?

	bool operator==(const Move& move)	const;
	bool operator!=(const Move& move)	const;
	explicit operator bool(void)		const;
	explicit operator uint16_t(void)	const;
private:
	uint16_t data;
};


#endif //CHESS_MOVE_HPP
