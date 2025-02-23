//
// Created by marijn on 2/6/25.
//

#ifndef CHESS_BOT_MOVE_GEN_HPP
#define CHESS_BOT_MOVE_GEN_HPP
#include "move.hpp"
#include "position.hpp"
#include "magic.hpp"


#define MAX_MOVE 256


enum gen_type {
    CAPTURES,
    QUIETS,
    EVASIONS,
    NON_EVASIONS,
    LEGAL
};


template<gen_type type>
Move* generate(const Position& pos, Move* move_list);
Move* generate(const Position& pos, Move* move_list);  // generate all


#endif //CHESS_BOT_MOVE_GEN_HPP
