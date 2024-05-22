import curses
import time
from curses import wrapper
from time import sleep

from chess import hello


b = 7
chars = [
	" ", "♝", "♚", "♞", "♟", "♛", "♜",
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

def main(stdscr):
	curses.curs_set(0)

	curses.init_pair(1, 0xfa, curses.COLOR_BLACK)
	curses.init_pair(2, 0xfa, curses.COLOR_WHITE)
	curses.init_pair(3, 0xe8, curses.COLOR_BLACK)
	curses.init_pair(4, 0xe8, curses.COLOR_WHITE)

	stdscr.clear()

	for y in range(8):
		for x in range(8):
			stdscr.addstr(y, x * 2, "  ", curses.color_pair(1 + ((x + y) % 2)))

	for i, p in enumerate(board):
		y = i // 8
		x = i % 8
		stdscr.addch(y, x * 2, chars[p % 7], curses.color_pair(1 + ((x + y) % 2) + 2 * (p > 7)))

	stdscr.refresh()
	x, y = 0, 0
	run = True
	while run:
		stdscr.refresh()
		key = stdscr.getkey()

		p = board[x + 8 * y]
		stdscr.addstr(y, x * 2, f"{chars[p % 7]} ", curses.color_pair(1 + ((x + y) % 2) + 2 * (p > 7)))

		if key == "KEY_LEFT":	x = (x - 1) % 8
		if key == "KEY_RIGHT":	x = (x + 1) % 8
		if key == "KEY_UP":		y = (y - 1) % 8
		if key == "KEY_DOWN":	y = (y + 1) % 8
		if key == "Q":			run = False

		p = board[x + 8 * y]
		stdscr.addstr(y, x * 2, f"{chars[p % 7]} ", curses.color_pair(1 + ((x + y) % 2) + 2 * (p > 7)) | curses.A_REVERSE)
	curses.endwin()


wrapper(main)