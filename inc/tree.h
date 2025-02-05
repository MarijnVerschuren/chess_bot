//
// Created by marijn on 2/4/25.
//

#ifndef CHESS_BOT_TREE_H
#define CHESS_BOT_TREE_H
#include "vector.h"



typedef struct {
	void* data;
	vector_t children;
} tree_t;


void init_tree(tree_t* tree, void* data, uint16_t unit_size, uint32_t cap);


#endif //CHESS_BOT_TREE_H
