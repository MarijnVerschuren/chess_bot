//
// Created by marijn on 2/4/25.
//

#include "vector.h"



static inline void vector_resize(vector_t* vec) {
	uint32_t	new_cap =	vec->capacity * VECTOR_GROWTH;
	void*		new_ptr =	calloc(new_cap, vec->unit_size);
	memcpy(new_ptr, vec->ptr, vec->unit_size * vec->size);
	free(vec->ptr); vec->ptr = new_ptr;
	vec->capacity = new_cap;
}



void init_vector(vector_t* vec, uint16_t unit_size, uint32_t cap){
	vec->ptr = calloc(cap, unit_size);
	vec->size = 0;
	vec->capacity = cap;
	vec->unit_size = unit_size;
}

void vector_add(vector_t* vec, void* unit) {
	if (vec->size + vec->unit_size < vec->capacity) { vector_resize(vec); }
	memcpy(&((uint8_t*)vec->ptr)[vec->unit_size * vec->size], unit, vec->unit_size);
	vec->size += vec->unit_size;
}

void* vector_index(vector_t* vec, uint32_t index) {
	return &((uint8_t*)vec->ptr)[vec->unit_size * index];
}
