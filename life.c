#include <ncurses.h>
#include <stdlib.h>

#define POS(X,Y)	Y * COLS * X

void init_world(bool *world);
void draw_world(bool *world);

int main(void)
{
	srand(time(NULL));
	initscr();
	clear();
	noecho();
	cbreak();
	curs_set(0);

	printw("%d %d", LINES, COLS);
	bool world[LINES * COLS];
	draw_world(world);

	refresh();
	getch();
	endwin();

	return 0;
}

void init_world(bool *world)
{
	int y, x;
	for(y = 0; y < LINES; y++) {
		for(x = 0; x < COLS; x++) {
			world[y * COLS + x] = rand() % 2;
		}
	}
}

void draw_world(bool *world)
{
	int y, x;
	for(y = 0; y < LINES; y++) {
		for(x = 0; x < COLS; x++) {
			if(world[y*COLS + x])
				mvprintw(y, x, "%d", (int)world[y*COLS+x]);
		}
	}
}
