#include <ncurses.h>

int main(){
	initscr();
	raw();
	keypad(stdscr, TRUE);
	mvaddch(3, 2, 'b' | A_UNDERLINE);
	refresh();
	getch();
	endwin();

	return 0;
}
