//
// Created by marijn on 2/11/25.
//

#ifndef CHESS_BOT_MISC_HPP
#define CHESS_BOT_MISC_HPP
#include "types.hpp"


#define _ND [[nodiscard]]
#define _MU [[maybe_unused]]

#define CTZ(x) __builtin_ctzll(x)
// TODO: __builtin_prefetch


#ifdef NDEBUG
#define assert(EX)
#else
#define assert(EX) (void)((EX) || (__assert (#EX, __FILE__, __LINE__),0))
#endif

extern "C" void __assert (const char *msg, const char *file, int line);


static inline uint8_t pop_lsb(bit_board_t& bb) {
	uint8_t b = CTZ(bb);
	bb &= bb - 1;
	return b;
}


#endif //CHESS_BOT_MISC_HPP
