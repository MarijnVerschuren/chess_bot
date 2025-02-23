//
// Created by marijn on 2/6/25.
//

#include "move_gen.hpp"



/*!<
 * special move generators
 * */
template<gen_type type, int8_t dir, bool enemy>
Move* make_promotions(Move* move_list, _MU sq_t sq) {
    constexpr bool all = type == EVASIONS || type == NON_EVASIONS;
    if constexpr (type == CAPTURES || all) {
		*move_list++ = Move(sq - dir, sq, PROMOTION, QUEEN);
	}

    if constexpr ((type == CAPTURES && enemy) || (type == QUIETS && !enemy) || all) {
        *move_list++ = Move(sq - dir, sq, PROMOTION, ROOK);
        *move_list++ = Move(sq - dir, sq, PROMOTION, BISHOP);
        *move_list++ = Move(sq - dir, sq, PROMOTION, KNIGHT);
    }

    return move_list;
}


/*!<
 * piecewise move generators
 * */
template<color_t stm, gen_type type>
Move* generate_pawn_moves(const Position& pos, Move* move_list, bit_board_t target) {
    constexpr bit_board_t rank_6 =	(stm == WHITE ? 0x00FF000000000000ULL : 0x000000000000FF00ULL);
    constexpr bit_board_t rank_2 =	(stm == WHITE ? 0x0000000000FF0000ULL : 0x0000FF0000000000ULL);

    constexpr int8_t up =			pawn_push(stm);
    constexpr int8_t up_r =			(stm == WHITE ? 9 : -9);
    constexpr int8_t up_l =			(stm == WHITE ? 7 : -7);

    const bit_board_t empty =		~pos.piece(ALL);
    const bit_board_t enemies =		type == EVASIONS ? pos.checkers_g() : pos.piece(!stm, ALL);

    bit_board_t pawns =				pos.piece(stm, PAWN);
    bit_board_t pawns_on_6 =		pawns & rank_6;
	pawns &= ~rank_6;

	if constexpr (type != CAPTURES) {
        bit_board_t push_1 = shift<up>(pawns) & empty;
        bit_board_t push_2 = shift<up>(push_1 & rank_2) & empty;
		if constexpr (type == EVASIONS) {	// consider only blockers
            push_1 &= target;
            push_2 &= target;
        }
		sq_t sq;
		for (;push_1;) {	// single push moves
			sq = pop_lsb(push_1);
			*move_list++ = Move(sq - up, sq);
		}
		for (;push_2;) {	// double push moves
			sq = pop_lsb(push_2);
			*move_list++ = Move(sq - up - up, sq);
		}
	}

	if (pawns_on_6) {
		bit_board_t attack_up_r = shift<up_r>(pawns_on_6) & enemies;
		bit_board_t attack_up_l = shift<up_l>(pawns_on_6) & enemies;
		bit_board_t push = shift<up>(pawns_on_6) & empty;

		if constexpr (type == EVASIONS) { push &= target; }

		for (;attack_up_r;) {
			move_list = make_promotions<type, up_r, true>(move_list, pop_lsb(attack_up_r));
		}
		for (;attack_up_l;) {
			move_list = make_promotions<type, up_l, true>(move_list, pop_lsb(attack_up_l));
		}
		for (;push;) {
			move_list = make_promotions<type, up, false>(move_list, pop_lsb(push));
		}
	}

	// normal and en-passant captures
    if constexpr (type == CAPTURES || type == EVASIONS || type == NON_EVASIONS) {
        bit_board_t attack_0 = shift<up_r>(pawns) & enemies;
        bit_board_t attack_1 = shift<up_l>(pawns) & enemies;

		sq_t sq;
        for (;attack_0;) {
			sq = pop_lsb(attack_0);
            *move_list++ = Move(sq - up_r, sq);
        }
        for (;attack_1;) {
			sq = pop_lsb(attack_1);
            *move_list++ = Move(sq - up_l, sq);
        }

        if (pos.en_passant_sq_g() != SQ_NONE) {
            // en passant capture cannot resolve a discovered check
            if (type == EVASIONS && (target & (pos.en_passant_sq_g() + up))) { return move_list; }

            attack_0 = pawns & pawn_attacks[!stm][pos.en_passant_sq_g()];
            assert(attack_0);

            for (;attack_0;) {
				*move_list++ = Move(pop_lsb(attack_0), pos.en_passant_sq_g(), EN_PASSANT);
			}
        }
    }

	return move_list;
}

template<color_t stm, piece_t piece>
Move* generate_moves(const Position& pos, Move* move_list, bit_board_t target) {
	assert(piece != KING && piece != PAWN);
    bit_board_t bb = pos.piece(stm, piece);
    bit_board_t occ = pos.piece(ALL);

    for (;bb;) {
        sq_t sq = pop_lsb(bb);

        bit_board_t attack;
		if constexpr (piece == KNIGHT)		{ attack = knight_attacks[sq] & target; }
		else if constexpr (piece == BISHOP)	{ attack = index_magic_bishop(sq, occ) & target; }
		else if constexpr (piece == ROOK)	{ attack = index_magic_rook(sq, occ) & target; }
		else if constexpr (piece == QUEEN)	{ attack = index_magic_queen(sq, occ) & target; }

        for (;attack;) {
            *move_list++ = Move(sq, pop_lsb(attack));
    	}
	}

	return move_list;
}


/*!<
 * type wise move generator
 * */
template<color_t stm, gen_type type>
Move* generate_all(const Position& pos, Move* move_list) {
    const sq_t			ksq = CTZ(pos.piece(stm, KING));
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
	const sq_t ksq = CTZ(pos.piece(stm, KING));
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