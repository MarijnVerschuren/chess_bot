def print_table(table: list[int], int_size: int = 8, unsigned: bool = True) -> None:
	print(f"{'u' if unsigned else ''}int{int_size}_t table[{len(table)}] = {'{'}")
	for x in table:
		print("\t0x" + f"{x:#0{(int_size // 4) + 2}X}{'U' if unsigned else ''}{'L' * (int_size // 32)},"[2:])
	print("};")


def print_bb(bb: int) -> None:
	for y in range(8):
		for x in range(8):
			print((bb >> (63 - ((7 - x) + y * 8))) & 1, end="  ")
		print()
	print("\n")


bishop_table: list[int] = []
def gen_bishop_table() -> None:
	for i in range(64):
		result = 0
		xp = i % 8
		yp = i // 8
		for x, y in zip(range(xp + 1, 7), range(yp + 1, 7)):		result |= (1 << (x + 8 * y))
		for x, y in zip(range(xp + 1, 7), range(1, yp)[::-1]):		result |= (1 << (x + 8 * y))
		for x, y in zip(range(1, xp)[::-1], range(yp + 1, 7)):		result |= (1 << (x + 8 * y))
		for x, y in zip(range(1, xp)[::-1], range(1, yp)[::-1]):	result |= (1 << (x + 8 * y))
		bishop_table.append(result)
		
		
"""
		((pbb->board[WHITE | KNIGHT] & ~(FILE_A | FILE_B)) << 6)	|
		((pbb->board[WHITE | KNIGHT] & ~(FILE_A | FILE_B)) >> 10)	|
		((pbb->board[WHITE | KNIGHT] & ~(FILE_G | FILE_H)) >> 6)	|
		((pbb->board[WHITE | KNIGHT] & ~(FILE_G | FILE_H)) << 10)	|
		((pbb->board[WHITE | KNIGHT] & ~FILE_A) << 15)				|
		((pbb->board[WHITE | KNIGHT] & ~FILE_A) >> 17)				|
		((pbb->board[WHITE | KNIGHT] & ~FILE_H) >> 15)				|
		((pbb->board[WHITE | KNIGHT] & ~FILE_H) << 17)
"""

knight_table: list[int] = []
def gen_knight_table() -> None:
	for i in range(64):
		result = 0
		x = i % 8
		if x != 0:
			result |= (1 << (i + 15))
			result |= ((1 << i) >> 17)
		if x != 7:
			result |= (1 << (i + 17))
			result |= ((1 << i) >> 15)
		if x > 1:
			result |= (1 << (i + 6))
			result |= ((1 << i) >> 10)
		if x < 6:
			result |= (1 << (i + 10))
			result |= ((1 << i) >> 6)
		knight_table.append(result & 0xFFFFFFFFFFFFFFFF)


if __name__ == "__main__":
	gen_knight_table()
	for x in range(64):
		print_bb(knight_table[x])
	print_table(knight_table, 64, True)
