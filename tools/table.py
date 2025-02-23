def print_table(table: list[int], int_size: int = 8, unsigned: bool = True) -> None:
	print(f"{'u' if unsigned else ''}int{int_size}_t table[{len(table)}] = {'{'}")
	for x in table:
		print("\t0x" + f"{x:#0{(int_size // 4) + 2}X}{'U' if unsigned else ''}{'L' * (int_size // 32)},"[2:])
	print("};")
	
def print_table_2D(table: list[list[int]], int_size: int = 8, unsigned: bool = True) -> None:
	print(f"{'u' if unsigned else ''}int{int_size}_t table[{len(table)}] = {'{'}\n", end="\t")
	for tab in table:
		print("{")
		for x in tab:
			print("\t\t0x" + f"{x:#0{(int_size // 4) + 2}X}{'U' if unsigned else ''}{'L' * (int_size // 32)},"[2:])
		print("\t},", end=" ")
	print("\n};")

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
		for x, y in zip(range(xp, 8), range(yp, 8)):			result |= (1 << (x + 8 * y))
		for x, y in zip(range(xp, 8), range(0, yp)[::-1]):		result |= (1 << (x + 8 * y))
		for x, y in zip(range(0, xp)[::-1], range(yp, 8)):		result |= (1 << (x + 8 * y))
		for x, y in zip(range(0, xp)[::-1], range(0, yp)[::-1]):result |= (1 << (x + 8 * y))
		bishop_table.append(result)
		

rook_table: list[int] = []
def gen_rook_table() -> None:
	for i in range(64):
		xp = i % 8
		yp = i // 8
		result = (
			(0x0101010101010101 << xp) |
			(0x00000000000000FF << (8 * yp))
		)
		rook_table.append(result)
		


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
		

def pos_to_bb(sq: int) -> int:
	return (1 << sq) & 0xFFFFFFFFFFFFFFFF


pawn_tables: list[list[int]] = [[],[]]
def gen_pawn_tables() -> None:
	for i in range(64):
		# black
		pawn_tables[0].append((
			((pos_to_bb(i) & ~0x8080808080808080) >> 7) |
			((pos_to_bb(i) & ~0x0101010101010101) >> 9)) & 0xFFFFFFFFFFFFFFFF
		)
		# white
		pawn_tables[1].append((
			((pos_to_bb(i) & ~0x0101010101010101) << 7) |
			((pos_to_bb(i) & ~0x8080808080808080) << 9)) & 0xFFFFFFFFFFFFFFFF
		)


pseudo_bishop_table: list[int] = []
pseudo_rook_table: list[int] = []
def gen_pseudo_tables() -> None:
	for i in range(64):
		x = i % 8; y = i // 8
		pseudo_rook_table.append(((0x0101010101010101 << x) | (0xFF << (y << 3))) & ~(1 << i))
		bbb = 0
		for xb, yb in zip(range(x + 1, 8), range(y + 1, 8)):
			bbb |= 1 << (xb + 8 * yb)
		for xb, yb in zip(range(x + 1, 8), range(y)[::-1]):
			bbb |= 1 << (xb + 8 * yb)
		for xb, yb in zip(range(x)[::-1], range(y + 1, 8)):
			bbb |= 1 << (xb + 8 * yb)
		for xb, yb in zip(range(x)[::-1], range(y)[::-1]):
			bbb |= 1 << (xb + 8 * yb)
		pseudo_bishop_table.append(bbb & ~(1 << i))
		
		
between_table: list[list[int]] = []
def gen_between_table() -> None:
	for a in range(64):
		xa = a % 8; ya = a // 8
		between_table.append([])
		for b in range(64):
			xb = b % 8; yb = b // 8
			bb = 0
			if xa == xb:
				for y in range(*[sum(z) for z in zip(sorted([ya, yb]), [0, 1])]):
					bb |= 1 << (xa + 8 * y)
			elif ya == yb:
				for x in range(*[sum(z) for z in zip(sorted([xa, xb]), [0, 1])]):
					bb |= 1 << (x + 8 * ya)
			elif abs(xa - xb) == abs(ya - yb):
				xas, xbs = sorted([xa, xb])
				yas, ybs = sorted([ya, yb])
				for x, y in zip(range(xas + 1, xbs)[::(1 - 2 * (xas != xa))], range(yas + 1, ybs)[::(1 - 2 * (yas != ya))]):
					bb |= 1 << (x + 8 * y)
				
			bb &= ~((1 << (xa + 8 * ya)) | (1 << (xb + 8 * yb)))
			between_table[a].append(bb)
			
			
line_table: list[list[int]] = []
def gen_line_table() -> None:
	gen_rook_table()
	gen_bishop_table()
	for a in range(64):
		line_table.append([])
		for b in range(64):
			line_table[a].append(
				(((rook_table[a] & rook_table[b]) * ((rook_table[a] & (1 << b)) != 0)) |
				((bishop_table[a] & bishop_table[b]) * ((bishop_table[a] & (1 << b)) != 0))) * (a != b)
			)


castle_table: list[int] = []
def gen_castle_table() -> None:
	gen_between_table()
	
	kfrom =	[4, 4, 4 ^ 56, 4 ^ 56]
	kto =	[6, 2, 6 ^ 56, 2 ^ 56]
	rfrom =	[7, 0, 7 ^ 56, 0 ^ 56]
	rto =	[5, 3, 5 ^ 56, 3 ^ 56]
	for k, r in zip(zip(kfrom, kto), zip(rfrom, rto)):
		kf, kt = k
		rf, rt = r
		castle_table.append(
			(between_table[kf][kt] |
			between_table[rf][rt]) &
			~((1 << kf) | (1 << rf))
		)
		


if __name__ == "__main__":
	gen_castle_table()
	for i in range(4):
		print_bb(castle_table[i])
	
	print_table(castle_table, 64)
		
	# gen_line_table()
	# for a in range(64):
	# 	print(f"LINE{a}")
	# 	for b in range(64):
	# 		print(f"{a} -> {b}")
	# 		print_bb(line_table[a][b])
	# print_table_2D(line_table, 64, True)
