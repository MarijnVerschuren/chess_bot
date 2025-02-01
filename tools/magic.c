//
// Created by marijn on 1/31/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


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

const uint8_t rook_bits[64] = {
	12, 11, 11, 11, 11, 11, 11, 12,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	12, 11, 11, 11, 11, 11, 11, 12
};

const uint8_t bishop_bits[64] = {
	6, 5, 5, 5, 5, 5, 5, 6,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 7, 7, 7, 7, 5, 5,
	5, 5, 7, 9, 9, 7, 5, 5,
	5, 5, 7, 9, 9, 7, 5, 5,
	5, 5, 7, 7, 7, 7, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	6, 5, 5, 5, 5, 5, 5, 6
};

uint32_t rook_table_offset[64] = {
	0x00000000UL,
	0x00001000UL,
	0x00001800UL,
	0x00002000UL,
	0x00002800UL,
	0x00003000UL,
	0x00003800UL,
	0x00004000UL,
	0x00005000UL,
	0x00005800UL,
	0x00005C00UL,
	0x00006000UL,
	0x00006400UL,
	0x00006800UL,
	0x00006C00UL,
	0x00007000UL,
	0x00007800UL,
	0x00008000UL,
	0x00008400UL,
	0x00008800UL,
	0x00008C00UL,
	0x00009000UL,
	0x00009400UL,
	0x00009800UL,
	0x0000A000UL,
	0x0000A800UL,
	0x0000AC00UL,
	0x0000B000UL,
	0x0000B400UL,
	0x0000B800UL,
	0x0000BC00UL,
	0x0000C000UL,
	0x0000C800UL,
	0x0000D000UL,
	0x0000D400UL,
	0x0000D800UL,
	0x0000DC00UL,
	0x0000E000UL,
	0x0000E400UL,
	0x0000E800UL,
	0x0000F000UL,
	0x0000F800UL,
	0x0000FC00UL,
	0x00010000UL,
	0x00010400UL,
	0x00010800UL,
	0x00010C00UL,
	0x00011000UL,
	0x00011800UL,
	0x00012000UL,
	0x00012400UL,
	0x00012800UL,
	0x00012C00UL,
	0x00013000UL,
	0x00013400UL,
	0x00013800UL,
	0x00014000UL,
	0x00015000UL,
	0x00015800UL,
	0x00016000UL,
	0x00016800UL,
	0x00017000UL,
	0x00017800UL,
	0x00018000UL
};

uint32_t bishop_table_offset[64] = {
	0x00000000UL,
	0x00000040UL,
	0x00000060UL,
	0x00000080UL,
	0x000000A0UL,
	0x000000C0UL,
	0x000000E0UL,
	0x00000100UL,
	0x00000140UL,
	0x00000160UL,
	0x00000180UL,
	0x000001A0UL,
	0x000001C0UL,
	0x000001E0UL,
	0x00000200UL,
	0x00000220UL,
	0x00000240UL,
	0x00000260UL,
	0x00000280UL,
	0x00000300UL,
	0x00000380UL,
	0x00000400UL,
	0x00000480UL,
	0x000004A0UL,
	0x000004C0UL,
	0x000004E0UL,
	0x00000500UL,
	0x00000580UL,
	0x00000780UL,
	0x00000980UL,
	0x00000A00UL,
	0x00000A20UL,
	0x00000A40UL,
	0x00000A60UL,
	0x00000A80UL,
	0x00000B00UL,
	0x00000D00UL,
	0x00000F00UL,
	0x00000F80UL,
	0x00000FA0UL,
	0x00000FC0UL,
	0x00000FE0UL,
	0x00001000UL,
	0x00001080UL,
	0x00001100UL,
	0x00001180UL,
	0x00001200UL,
	0x00001220UL,
	0x00001240UL,
	0x00001260UL,
	0x00001280UL,
	0x000012A0UL,
	0x000012C0UL,
	0x000012E0UL,
	0x00001300UL,
	0x00001320UL,
	0x00001340UL,
	0x00001380UL,
	0x000013A0UL,
	0x000013C0UL,
	0x000013E0UL,
	0x00001400UL,
	0x00001420UL,
	0x00001440UL
};

uint64_t magic_rook_attack_table[102400] = {};
uint64_t magic_bishop_attack_table[5248] = {};

// random functions
uint64_t random_uint64() {
	uint64_t u1, u2, u3, u4;
	u1 = (uint64_t)(random()) & 0xFFFF; u2 = (uint64_t)(random()) & 0xFFFF;
	u3 = (uint64_t)(random()) & 0xFFFF; u4 = (uint64_t)(random()) & 0xFFFF;
	return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}
uint64_t random_uint64_fb() {
	return random_uint64() & random_uint64() & random_uint64();
}

// bit operations
uint8_t btc(uint64_t b) {
	uint8_t r;
	for(r = 0; b; r++, b &= b - 1);
	return r;
}
uint8_t pop_bit(uint64_t *bb) {
	uint64_t b = *bb ^ (*bb - 1);
	uint32_t fold = ((b & 0xFFFFFFFFUL) ^ (b >> 32));
	*bb &= (*bb - 1);
	return bit_table[(fold * 0x783A9B23) >> 26];
}

// table index to mask
uint64_t index_to_bb(uint16_t index, uint8_t bits, uint64_t mask) {
	uint64_t result = 0ULL;
	uint8_t i, j;
	for(i = 0; i < bits; i++) {
		j = pop_bit(&mask);
		if(index & (1 << i)) result |= (1ULL << j);
	}
	return result;
}

// move masks
uint64_t rook_mask(uint8_t sq) {
	uint64_t result = 0ULL;
	int8_t rk = sq / 8, fl = sq % 8, r, f;
	for(r = rk + 1; r <= 6; r++) result |= (1ULL << (fl + r * 8));
	for(r = rk - 1; r >= 1; r--) result |= (1ULL << (fl + r * 8));
	for(f = fl + 1; f <= 6; f++) result |= (1ULL << (f + rk * 8));
	for(f = fl - 1; f >= 1; f--) result |= (1ULL << (f + rk * 8));
	return result;
}
uint64_t bishop_mask(uint8_t sq) {
	uint64_t result = 0ULL;
	int8_t rk = sq/8, fl = sq%8, r, f;
	for(r = rk + 1, f = fl + 1; r <= 6 && f <= 6; r++, f++) result |= (1ULL << (f + r * 8));
	for(r = rk + 1, f = fl - 1; r <= 6 && f >= 1; r++, f--) result |= (1ULL << (f + r * 8));
	for(r = rk - 1, f = fl + 1; r >= 1 && f <= 6; r--, f++) result |= (1ULL << (f + r * 8));
	for(r = rk - 1, f = fl - 1; r >= 1 && f >= 1; r--, f--) result |= (1ULL << (f + r * 8));
	return result;
}
// attacks
uint64_t rook_attack(uint8_t sq, uint64_t block) {
	uint64_t result = 0ULL;
	int8_t rk = sq / 8, fl = sq % 8, r, f;
	for(r = rk + 1; r <= 7; r++) {
		result |= (1ULL << (fl + r * 8));
		if(block & (1ULL << (fl + r * 8))) break;
	}
	for(r = rk - 1; r >= 0; r--) {
		result |= (1ULL << (fl + r * 8));
		if(block & (1ULL << (fl + r * 8))) break;
	}
	for(f = fl + 1; f <= 7; f++) {
		result |= (1ULL << (f + rk * 8));
		if(block & (1ULL << (f + rk * 8))) break;
	}
	for(f = fl - 1; f >= 0; f--) {
		result |= (1ULL << (f + rk * 8));
		if(block & (1ULL << (f + rk * 8))) break;
	}
	return result;
}
uint64_t bishop_attack(uint8_t sq, uint64_t block) {
	uint64_t result = 0ULL;
	int8_t rk = sq / 8, fl = sq % 8, r, f;
	for(r = rk + 1, f = fl + 1; r <= 7 && f <= 7; r++, f++) {
		result |= (1ULL << (f + r*8));
		if(block & (1ULL << (f + r * 8))) break;
	}
	for(r = rk + 1, f = fl - 1; r <= 7 && f >= 0; r++, f--) {
		result |= (1ULL << (f + r * 8));
		if(block & (1ULL << (f + r * 8))) break;
	}
	for(r = rk - 1, f = fl + 1; r >= 0 && f <= 7; r--, f++) {
		result |= (1ULL << (f + r * 8));
		if(block & (1ULL << (f + r * 8))) break;
	}
	for(r = rk - 1, f = fl - 1; r >= 0 && f >= 0; r--, f--) {
		result |= (1ULL << (f + r * 8));
		if(block & (1ULL << (f + r * 8))) break;
	}
	return result;
}

// bitmask to index
uint16_t transform(uint64_t b, uint64_t magic, uint8_t bits) {
	return (uint16_t)((b * magic) >> (64 - bits));
}

// find magics
uint64_t find_rook_magic(uint8_t sq) {
	uint64_t mask, attack[4096], block[4096], used[4096], magic;
	uint32_t k;
	uint16_t i, j;
	uint8_t n, fail, mbtc = rook_bits[sq];
	mask = rook_mask(sq);
	n = btc(mask);

	for(i = 0; i < (1 << n); i++) {
		block[i] = index_to_bb(i, n, mask);
		attack[i] = rook_attack(sq, block[i]);
	}

	for(k = 0; k < 100000000; k++) {
		magic = random_uint64_fb();
		// reject random number
		if(btc((mask * magic) & 0xFF00000000000000ULL) < 6) continue;
		for(i = 0; i < 4096; i++) used[i] = 0ULL;
		for(i = 0, fail = 0; !fail && i < (1 << n); i++) {
			j = transform(block[i], magic, mbtc);
			if(used[j] == 0ULL) used[j] = attack[i];
			else if(used[j] != attack[i]) fail = 1;
		}
		if(!fail) {
			for (uint32_t l = 0; l < (1 << n); l++) {
				magic_rook_attack_table[
					rook_table_offset[sq] + l
				] = used[l];
			}
			return magic;
		}
	} return 0ULL;
}

uint64_t find_bishop_magic(uint8_t sq) {
	uint64_t mask, attack[512], block[512], used[512], magic;
	uint32_t k;
	uint16_t i, j;
	uint8_t n, fail, mbtc = bishop_bits[sq];
	mask = bishop_mask(sq);
	n = btc(mask);

	for(i = 0; i < (1 << n); i++) {
		block[i] = index_to_bb(i, n, mask);
		attack[i] = bishop_attack(sq, block[i]);
	}

	for(k = 0; k < 100000000; k++) {
		magic = random_uint64_fb();
		// reject random number
		if(btc((mask * magic) & 0xFF00000000000000ULL) < 6) continue;
		for(i = 0; i < 512; i++) used[i] = 0ULL;
		for(i = 0, fail = 0; !fail && i < (1 << n); i++) {
			j = transform(block[i], magic, mbtc);
			if(used[j] == 0ULL) used[j] = attack[i];
			else if(used[j] != attack[i]) fail = 1;
		}
		if(!fail) {
			for (uint32_t l = 0; l < (1 << n); l++) {
				magic_bishop_attack_table[
					bishop_table_offset[sq] + l
				] = used[l];
			}
			return magic;
		}
	} return 0ULL;
}


int main() {
	uint8_t sq;

	printf("const uint64_t rook_magics[64] = {\n");
	for(sq = 0; sq < 64; sq++) {
		printf("\t0x%016llXULL,\n", find_rook_magic(sq));
	} printf("};\n\n");

	printf("const uint64_t bishop_magics[64] = {\n");
	for(sq = 0; sq < 64; sq++) {
		printf("\t0x%016llXULL,\n", find_bishop_magic(sq));
	} printf("};\n\n");


	printf("const uint64_t magic_rook_moves[102400] = {\n");
	for(uint32_t i = 0; i < 102400; i += 8) {
		printf("\t0x%016llXULL, ", magic_rook_attack_table[i + 0]);
		printf("\t0x%016llXULL, ", magic_rook_attack_table[i + 1]);
		printf("\t0x%016llXULL, ", magic_rook_attack_table[i + 2]);
		printf("\t0x%016llXULL, ", magic_rook_attack_table[i + 3]);
		printf("\t0x%016llXULL, ", magic_rook_attack_table[i + 4]);
		printf("\t0x%016llXULL, ", magic_rook_attack_table[i + 5]);
		printf("\t0x%016llXULL, ", magic_rook_attack_table[i + 6]);
		printf("\t0x%016llXULL,\n", magic_rook_attack_table[i + 7]);
	} printf("};\n\n");

	printf("const uint64_t magic_bishop_moves[5248] = {\n");
	for(uint32_t i = 0; i < 5248; i += 8) {
		printf("\t0x%016llXULL, ", magic_bishop_attack_table[i + 0]);
		printf("\t0x%016llXULL, ", magic_bishop_attack_table[i + 1]);
		printf("\t0x%016llXULL, ", magic_bishop_attack_table[i + 2]);
		printf("\t0x%016llXULL, ", magic_bishop_attack_table[i + 3]);
		printf("\t0x%016llXULL, ", magic_bishop_attack_table[i + 4]);
		printf("\t0x%016llXULL, ", magic_bishop_attack_table[i + 5]);
		printf("\t0x%016llXULL, ", magic_bishop_attack_table[i + 6]);
		printf("\t0x%016llXULL,\n", magic_bishop_attack_table[i + 7]);
	} printf("};\n\n");

	return 0;
}

