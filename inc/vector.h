//
// Created by marijn on 2/4/25.
//

#ifndef CHESS_BOT_VECTOR_H
#define CHESS_BOT_VECTOR_H
#include <malloc.h>
#include <memory.h>

#include "types.h"

#define VECTOR_GROWTH 2



typedef struct {
	void*		ptr;
	uint64_t	size		: 24;
	uint64_t	capacity	: 24;
	uint64_t	unit_size	: 16;
} vector_t;


void init_vector(vector_t* vec, uint16_t unit_size, uint32_t cap);
void vector_add(vector_t* vec, void* unit);
void* vector_index(vector_t* vec, uint32_t index);


#endif //CHESS_BOT_VECTOR_H
