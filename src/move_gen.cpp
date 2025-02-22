//
// Created by marijn on 2/6/25.
//

#include "move_gen.hpp"


/*!<
 * piecewise move generators
 * */
template<color_t stm, gen_type type>
Move* generate_pawn_moves(const Position& pos, Move* move_list, uint64_t target) {

    constexpr bit_board_t rank_6 =	(stm == WHITE ? 0x00FF000000000000ULL : 0x000000000000FF00ULL);
    constexpr bit_board_t rank_2 =	(stm == WHITE ? 0x0000000000FF0000ULL : 0x0000FF0000000000ULL);

    constexpr uint8_t up =			pawn_push(stm);
    constexpr uint8_t up_r =		(stm == WHITE ? 9 : -9);
    constexpr uint8_t up_l =		(stm == WHITE ? 7 : -7);

    const bit_board_t empty =		~pos.piece(ALL);
    const bit_board_t enemies =		type == EVASIONS ? pos.checkers_g() : pos.piece(!stm, ALL);

    bit_board_t pawns =				pos.piece(stm, PAWN);
    bit_board_t pawns_on_6 =		pawns & rank_6;
	pawns &= ~rank_6;

	if constexpr (type != CAPTURES) {
        bit_board_t push_1 = shift<Up>(pawns) & empty;
        bit_board_t push_2 = shift<Up>(push_1 & rank_2) & empty;
		if constexpr (type == EVASIONS) {	// consider only blockers
            push_1 &= target;
            push_2 &= target;
        }

	}

	return move_list;
}

template<color_t stm, piece_t piece>
Move* generate_moves(const Position& pos, Move* move_list, uint64_t target) {
	// TODO
	return move_list;
}


/*!<
 * type wise move generator
 * */
template<color_t stm, gen_type type>
Move* generate_all(const Position& pos, Move* move_list) {
    const uint8_t		ksq = CTZ(pos.piece(stm, KING));
	const bit_board_t	checkers = pos.checkers_g();
    bit_board_t			target;

    // Skip generating non-king moves when in double check
    if (type != EVASIONS || !(checkers & (checkers - 1))) {
        target = type == EVASIONS     ? between_bb[ksq][CTZ(checkers)]
               : type == NON_EVASIONS ? ~pos.piece(stm, ALL)
               : type == CAPTURES     ? pos.piece(!stm, ALL)
                                      : ~pos.piece(ALL);  // QUIETS

        move_list = generate_pawn_moves<stm, type>(pos, move_list, target);
        move_list = generate_moves<stm, KNIGHT>(pos, move_list, target);
        move_list = generate_moves<stm, BISHOP>(pos, move_list, target);
        move_list = generate_moves<stm, ROOK>(pos, move_list, target);
        move_list = generate_moves<stm, QUEEN>(pos, move_list, target);
    }

    bit_board_t b = king_attacks[ksq] & (type == EVASIONS ? ~pos.piece(stm, ALL) : target);

    while (b) {
		*move_list++ = Move(ksq, pop_lsb(b));
	}

    if ((type == QUIETS || type == NON_EVASIONS) && pos.can_castle(stm & ANY_CASTLING)) {
		if (!pos.castle_impeded(KING_SIDE) && pos.can_castle(KING_SIDE)) {
			*move_list++ = Move(ksq, pos.castling_rook_square(KING_SIDE));
		}
		if (!pos.castle_impeded(QUEEN_SIDE) && pos.can_castle(QUEEN_SIDE)) {
			*move_list++ = Move(ksq, pos.castling_rook_square(QUEEN_SIDE));
		}
	}

    return move_list;
}


/*!<
 * exposed functionality
 * */
template<gen_type type>
Move* generate(const Position& pos, Move* move_list) {
	const color_t stm = pos.side_to_move_g();

    return stm == WHITE ? generate_all<WHITE, type>(pos, move_list)
						: generate_all<BLACK, type>(pos, move_list);
}


template Move* generate<CAPTURES>(const Position& pos, Move* move_list);
template Move* generate<QUIETS>(const Position& pos, Move* move_list);
template Move* generate<EVASIONS>(const Position& pos, Move* move_list);
template Move* generate<NON_EVASIONS>(const Position& pos, Move* move_list);
template Move* generate<LEGAL>(const Position& pos, Move* move_list);


Move* generate(const Position& pos, Move* move_list) {
	const color_t stm = pos.side_to_move_g();
	const uint8_t ksq = CTZ(pos.piece(stm, KING));
	const bit_board_t pinned = pos.king_blockers_g(stm) | pos.piece(stm, ALL);
	Move* current = move_list;

	move_list = pos.checkers_g() ?						// move_list = end + 1
		generate<EVASIONS>(pos, move_list):
		generate<NON_EVASIONS>(pos, move_list);

	while (current != move_list) {
		if (
			(((0b1ULL << current->src()) & pinned)	||	// move of pinned piece
			(current->src() == ksq)					||	// moving the king
			(current->type() == EN_PASSANT))		&&	// en passant
			!pos.legal(*current)						// illegal
		) {
			*current = *(--move_list);					// replace current with last entry
		} else {
			++current;									// check next move
		}
	}

	return move_list;
}