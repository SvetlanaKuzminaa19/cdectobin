#include <ncurses.h>

int main(){
	initscr();
	raw();
	keypad(stdscr, TRUE);
	addch('a' | A_BOLD | A_UNDERLINE);
	mvaddch(3, 2, 'b' | A_UNDERLINE);
	refresh();
	getch();
	endwin();

	return 0;
}
