//
// Created by marijn on 2/27/25.
//

#ifndef CHESS_BOT_SEARCH_HPP
#define CHESS_BOT_SEARCH_HPP
#include "move_gen.hpp"


// TODO: make multithreaded!!!
class Search {
public:
	Search() = default;  // TODO: search/threads management etc...

	int32_t search(Position& pos, uint8_t depth);



private:
};


#endif //CHESS_BOT_SEARCH_HPP
