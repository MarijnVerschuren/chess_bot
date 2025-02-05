//
// Created by marijn on 2/4/25.
//

#ifndef CHESS_BOT_MOVE_H
#define CHESS_BOT_MOVE_H
#include "types.h"


typedef enum {
	MOVE =			0x0U,
	PROMOTION =		0x1U,
	EN_PASSANT =	0x2U,
	CASTLE =		0x3U
} move_type_t;


typedef struct {
	uint16_t src		: 6;
	uint16_t dst		: 6;
	uint16_t promotion	: 2;	// piece - KNIGHT
	uint16_t type		: 2;	// move_type_t
} move_t;


#endif //CHESS_BOT_MOVE_H
