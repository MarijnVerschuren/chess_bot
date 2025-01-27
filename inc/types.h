//
// Created by marijn on 1/23/25.
//

#ifndef CHESS_BOT_TYPES_H
#define CHESS_BOT_TYPES_H


typedef char				int8_t;
typedef short				int16_t;
typedef long				int32_t;
typedef long long			int64_t;

typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned long		uint32_t;
typedef unsigned long long	uint64_t;

typedef unsigned long long	bit_board_t;

#define CTZ(x) __builtin_ctzll(x)

#endif //CHESS_BOT_TYPES_H
