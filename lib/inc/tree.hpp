//
// Created by marijn on 12/23/24.
//

#ifndef CHESS_TREE_HPP
#define CHESS_TREE_HPP

#include "board.hpp"


class Board_Tree : public Board {
public:
	Board_Tree() = default;
	Board_Tree(Board& other);

	uint32_t generate(uint8_t depth);

private:
	uint32_t	child_count =	0;
	Board_Tree*	children =		nullptr;
};


#endif //CHESS_TREE_HPP
