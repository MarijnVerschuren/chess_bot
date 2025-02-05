//
// Created by marijn on 2/4/25.
//

#include "tree.h"



void init_tree(tree_t* tree, void* data, uint16_t unit_size, uint32_t cap) {
	tree->data = calloc(1, unit_size);
	memcpy(tree->data, data, unit_size);
	init_vector(&tree->children, unit_size, cap);
}