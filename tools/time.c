//
// Created by marijn on 2/1/25.
//
#include <stdint.h>
#include <stdio.h>
#include <time.h>



uint64_t tc = 0xFFFFFFFF;
uint64_t tn = 0x01a7154e19e6c440ULL;

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

uint8_t pop_bit(uint64_t bb) {
	uint64_t b = bb ^ (bb - 1);
	uint32_t fold = ((b & 0xFFFFFFFFUL) ^ (b >> 32));
	return bit_table[(fold * 0x783A9B23) >> 26];
}


void func_a() {
	for (uint64_t i = 0; i < tc; i++) {
		(void)pop_bit(tn);
	}
}

void func_b() {
	for (uint64_t i = 0; i < tc; i++) {
		(void)__builtin_ctzll(tn);
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


	printf("%d, \n", pop_bit(tn));
	printf("%d, \n", __builtin_ctzll(tn));

	return 0;
}