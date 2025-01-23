import curses
import time
from curses import wrapper
from time import sleep

from chess import *


chars = [
	" ", "♟", "♞", "♝", "♜", "♛", "♚"
]

board = Board()


def main(stdscr):
	curses.curs_set(0)

	curses.init_pair(1, 0xfa, curses.COLOR_BLACK)
	curses.init_pair(2, 0xfa, curses.COLOR_WHITE)
	curses.init_pair(3, 0xe8, curses.COLOR_BLACK)
	curses.init_pair(4, 0xe8, curses.COLOR_WHITE)

	stdscr.clear()

	for y in range(8):
		for x in range(8):
			p = board[x, y]
			stdscr.addstr(y, x * 2, f"{chars[p & 0x7]} ", curses.color_pair(1 + ((x + y) % 2) + 2 * (p >> 3)))

	stdscr.refresh()

	#stdscr.nodelay(True)

	x, y = 0, 0
	run = True
	while run:
		stdscr.refresh()
		key = stdscr.getkey()

		p = board[x, y]
		stdscr.addstr(y, x * 2, f"{chars[p & 0x7]} ", curses.color_pair(1 + ((x + y) % 2) + 2 * (p >> 3)))

		if key == "KEY_LEFT":	x = (x - 1) % 8
		if key == "KEY_RIGHT":	x = (x + 1) % 8
		if key == "KEY_UP":		y = (y - 1) % 8
		if key == "KEY_DOWN":	y = (y + 1) % 8
		if key == "Q":			run = False

		p = board[x, y]
		stdscr.addstr(y, x * 2, f"{chars[p & 0x7]} ", curses.color_pair(1 + ((x + y) % 2) + 2 * (p >> 3)) | curses.A_REVERSE)
	curses.endwin()

wrapper(main)