from rich import print


b = 7
chars = [
	" ", "♝", "♚", "♞", "♟", "♛", "♜",
	" ", "♗", "♔", "♘", "♙", "♕", "♖",
	" ", "♝", "♚", "♞", "♟", "♛", "♜"	# for inversion
]



board = [
	6, 3, 1, 5, 2, 1, 3, 6,
	4, 4, 4, 4, 4, 4, 4, 4,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	b+4, b+4, b+4, b+4, b+4, b+4, b+4, b+4,
	b+6, b+3, b+1, b+5, b+2, b+1, b+3, b+6,
]


if __name__ == "__main__":
	for i, p in enumerate(board):
		if i and i % 8 == 0: print()
		s = (i + i // 8) % 2

		print(f"{'[r]' if s else ''}{chars[p + 7 * s]} {'[/]' if s else ''}", end="")
	print()