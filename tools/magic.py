from random import randint


FILE: list[int] = [
	0x0101010101010101,
	0x0202020202020202,
	0x0404040404040404,
	0x0808080808080808,
	0x1010101010101010,
	0x2020202020202020,
	0x4040404040404040,
	0x8080808080808080
]
RANK: list[int] = [
	0x00000000000000FF,
	0x000000000000FF00,
	0x0000000000FF0000,
	0x00000000FF000000,
	0x000000FF00000000,
	0x0000FF0000000000,
	0x00FF000000000000,
	0xFF00000000000000,
]

rook_bitc: list[int] = [
	12, 11, 11, 11, 11, 11, 11, 12,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	12, 11, 11, 11, 11, 11, 11, 12
]

bishop_bitc: list[int] = [
	6, 5, 5, 5, 5, 5, 5, 6,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 7, 7, 7, 7, 5, 5,
	5, 5, 7, 9, 9, 7, 5, 5,
	5, 5, 7, 9, 9, 7, 5, 5,
	5, 5, 7, 7, 7, 7, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	6, 5, 5, 5, 5, 5, 5, 6,
]

rook_move_masks: list[int] = [
	0x000101010101017E,
	0x000202020202027C,
	0x000404040404047A,
	0x0008080808080876,
	0x001010101010106E,
	0x002020202020205E,
	0x004040404040403E,
	0x008080808080807E,
	0x0001010101017E00,
	0x0002020202027C00,
	0x0004040404047A00,
	0x0008080808087600,
	0x0010101010106E00,
	0x0020202020205E00,
	0x0040404040403E00,
	0x0080808080807E00,
	0x00010101017E0100,
	0x00020202027C0200,
	0x00040404047A0400,
	0x0008080808760800,
	0x00101010106E1000,
	0x00202020205E2000,
	0x00404040403E4000,
	0x00808080807E8000,
	0x000101017E010100,
	0x000202027C020200,
	0x000404047A040400,
	0x0008080876080800,
	0x001010106E101000,
	0x002020205E202000,
	0x004040403E404000,
	0x008080807E808000,
	0x0001017E01010100,
	0x0002027C02020200,
	0x0004047A04040400,
	0x0008087608080800,
	0x0010106E10101000,
	0x0020205E20202000,
	0x0040403E40404000,
	0x0080807E80808000,
	0x00017E0101010100,
	0x00027C0202020200,
	0x00047A0404040400,
	0x0008760808080800,
	0x00106E1010101000,
	0x00205E2020202000,
	0x00403E4040404000,
	0x00807E8080808000,
	0x007E010101010100,
	0x007C020202020200,
	0x007A040404040400,
	0x0076080808080800,
	0x006E101010101000,
	0x005E202020202000,
	0x003E404040404000,
	0x007E808080808000,
	0x7E01010101010100,
	0x7C02020202020200,
	0x7A04040404040400,
	0x7608080808080800,
	0x6E10101010101000,
	0x5E20202020202000,
	0x3E40404040404000,
	0x7E80808080808000
]


def print_bb(bb: int) -> None:
	for y in range(8):
		for x in range(8):
			print((bb >> (63 - ((7 - x) + y * 8))) & 1, end="  ")
		print()
	print("\n")
	

def print_table(table: list[int], c_like: bool = True) -> None:
	if c_like:
		print(f"uint64_t table[{len(table)}] = {'{'}")
		for x in table:
			print("\t0x" + f"{x:#0{18}X}ULL,"[2:])
		print("};")
	else:
		print("table: list[int] = [")
		for x in table:
			print("\t0x" + f"{x:#0{18}X},"[2:])
		print("]")
		
		
bit_table: list[int] = [
	63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
	51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
	26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
	58, 20, 37, 17, 36, 8
]

def pop_1st_bit(bb: int) -> tuple[int, int]:
	b = bb ^ (bb - 1)
	fold = (b & 0xffffffff) ^ (b >> 32)
	bb &= (bb - 1)
	return bb, bit_table[((fold * 0x783a9b23) & 0xffffffff) >> 26]


def btc(x: int) -> int:
	res = 0
	while (x):
		res += 1
		x &= x - 1
	return res


def random_uint64() -> int:
	return randint(0, 0xFFFFFFFFFFFFFFFF) & randint(0, 0xFFFFFFFFFFFFFFFF) & randint(0, 0xFFFFFFFFFFFFFFFF)


rook_magics: list[int] = []
bishop_magics: list[int] = []


def index_to_bb(index: int, bits: int, mask: int) -> int:
	result = 0;
	for i in range(bits):
		mask, j = pop_1st_bit(mask)
		if index & (1 << i):
			result |= (1 << j)
	return result


def rook_attack(sq: int, block: int) -> int:
	result = 0
	sqy = sq // 8
	sqx = sq % 8
	for x in range(sqx+1, 8):
		result |= (1 << (x + (sqy * 8)))
		if block & (1 << (x + (sqy * 8))):	break
	for x in range(sqx)[::-1]:
		result |= (1 << (x + (sqy * 8)))
		if block & (1 << (x + (sqy * 8))):	break
	for y in range(sqy+1, 8):
		result |= (1 << (sqx + (y * 8)))
		if block & (1 << (sqx + (y * 8))):	break
	for y in range(sqy)[::-1]:
		result |= (1 << (sqx + (y * 8)))
		if block & (1 << (sqx + (y * 8))):	break
	return result
	

def gen_rook_magic(sq: int, bits: int) -> int:
	mask: int = rook_move_masks[sq]
	mbtc: int = btc(mask)
	blockers = []
	attacks = []
	
	for i in range(1 << mbtc):
		blockers.append(index_to_bb(i, mbtc, mask))
		attacks.append(rook_attack(sq, blockers[i]))
	
	for _ in range(100000000):
		magic = random_uint64()
		if btc((mask * magic) & 0xFF00000000000000) < 6: continue
		used = [0] * (1 << mbtc)
		for i in range(1 << mbtc):
			j = ((blockers[i] * magic) & 0xFFFFFFFFFFFFFFFF) >> (64 - mbtc)
			if not used[j]: used[j] = attacks[i]
			elif used[j] != attacks[i]: break
		else: return magic
		

def gen_bishop_magic(sq: int, bits: int) -> int:
	pass


if __name__ == "__main__":
	#print_table(rook_move_masks)
	
	
	for sq in range(64):
		rook_magics.append(gen_rook_magic(sq, rook_bitc[sq]))
		#bishop_magics.append(gen_bishop_magic(sq, bishop_bitc[sq]))

	print_table(rook_magics)
	#print_table(bishop_magics)
	


#def gen_rook_move_masks():
#	for y in range(8):
#		for x in range(8):
#			mmask = RANK[y] | FILE[x]
#			mmask &= ~(0b1 << ((8 * y) + x))
#			if y != 0: mmask &= ~RANK[0]
#			if y != 7: mmask &= ~RANK[7]
#			if x != 0: mmask &= ~FILE[0]
#			if x != 7: mmask &= ~FILE[7]
#			rook_move_masks.append(mmask)

