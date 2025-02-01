//
// Created by marijn on 2/1/25.
//
#include <stdint.h>
#include <stdio.h>
#include <time.h>



typedef unsigned long long	bit_board_t;
static const bit_board_t FILE_A = 0x0101010101010101ULL;
static const bit_board_t FILE_B = 0x0202020202020202ULL;
static const bit_board_t FILE_C = 0x0404040404040404ULL;
static const bit_board_t FILE_D = 0x0808080808080808ULL;
static const bit_board_t FILE_E = 0x1010101010101010ULL;
static const bit_board_t FILE_F = 0x2020202020202020ULL;
static const bit_board_t FILE_G = 0x4040404040404040ULL;
static const bit_board_t FILE_H = 0x8080808080808080ULL;


const uint64_t knight_move_table[] = {
	0x0000000000020400ULL,
	0x0000000000050800ULL,
	0x00000000000A1100ULL,
	0x0000000000142200ULL,
	0x0000000000284400ULL,
	0x0000000000508800ULL,
	0x0000000000A01000ULL,
	0x0000000000402000ULL,
	0x0000000002040004ULL,
	0x0000000005080008ULL,
	0x000000000A110011ULL,
	0x0000000014220022ULL,
	0x0000000028440044ULL,
	0x0000000050880088ULL,
	0x00000000A0100010ULL,
	0x0000000040200020ULL,
	0x0000000204000402ULL,
	0x0000000508000805ULL,
	0x0000000A1100110AULL,
	0x0000001422002214ULL,
	0x0000002844004428ULL,
	0x0000005088008850ULL,
	0x000000A0100010A0ULL,
	0x0000004020002040ULL,
	0x0000020400040200ULL,
	0x0000050800080500ULL,
	0x00000A1100110A00ULL,
	0x0000142200221400ULL,
	0x0000284400442800ULL,
	0x0000508800885000ULL,
	0x0000A0100010A000ULL,
	0x0000402000204000ULL,
	0x0002040004020000ULL,
	0x0005080008050000ULL,
	0x000A1100110A0000ULL,
	0x0014220022140000ULL,
	0x0028440044280000ULL,
	0x0050880088500000ULL,
	0x00A0100010A00000ULL,
	0x0040200020400000ULL,
	0x0204000402000000ULL,
	0x0508000805000000ULL,
	0x0A1100110A000000ULL,
	0x1422002214000000ULL,
	0x2844004428000000ULL,
	0x5088008850000000ULL,
	0xA0100010A0000000ULL,
	0x4020002040000000ULL,
	0x0400040200000000ULL,
	0x0800080500000000ULL,
	0x1100110A00000000ULL,
	0x2200221400000000ULL,
	0x4400442800000000ULL,
	0x8800885000000000ULL,
	0x100010A000000000ULL,
	0x2000204000000000ULL,
	0x0004020000000000ULL,
	0x0008050000000000ULL,
	0x00110A0000000000ULL,
	0x0022140000000000ULL,
	0x0044280000000000ULL,
	0x0088500000000000ULL,
	0x0010A00000000000ULL,
	0x0020400000000000ULL,
};


const uint64_t tbb = (1 << 10) | (1 << 22);
const uint32_t tc = 1;


const uint8_t bit_table[64] = {
	63, 30,  3, 32, 25, 41, 22, 33,
	15, 50, 42, 13, 11, 53, 19, 34,
	61, 29,  2,	51, 21, 43, 45, 10,
	18, 47,  1, 54,  9, 57,  0, 35,
	62, 31, 40,  4, 49,  5, 52,	26,
	60,  6, 23, 44, 46, 27, 56, 16,
	 7, 39, 48, 24, 59, 14, 12, 55,
	38, 28, 58, 20, 37, 17, 36,  8
};
uint8_t pop_bit(uint64_t *bb) {
	uint64_t b = *bb ^ (*bb - 1);
	uint32_t fold = ((b & 0xFFFFFFFFUL) ^ (b >> 32));
	*bb &= (*bb - 1);
	return bit_table[(fold * 0x783A9B23) >> 26];
}

void func_a() {
	uint64_t res;
	for (uint32_t i = 0; i < tc; i++) {
		res = (
			((tbb & ~(FILE_A | FILE_B)) << 6)	|
			((tbb & ~(FILE_A | FILE_B)) >> 10)	|
			((tbb & ~(FILE_G | FILE_H)) >> 6)	|
			((tbb & ~(FILE_G | FILE_H)) << 10)	|
			((tbb & ~FILE_A) << 15)				|
			((tbb & ~FILE_A) >> 17)				|
			((tbb & ~FILE_H) >> 15)				|
			((tbb & ~FILE_H) << 17)
		);
		printf("%lx", res);
		(void)res;
	}
}

void func_b() {
	uint64_t res = 0, bb = tbb;
	for (uint32_t i = 0; i < tc; i++, res = 0, bb = tbb) {
		for (;bb;) { res |= knight_move_table[pop_bit(&bb)]; }
		printf("%lx", res);
		(void)res;
	}
}


int main(void) {
	clock_t begin, end;
	begin = clock();
	func_a();
	end = clock();
	printf("time A: %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
	begin = clock();
	func_b();
	end = clock();
	printf("time B: %f\n", (double)(end - begin) / CLOCKS_PER_SEC);

	return 0;
}