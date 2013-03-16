#include <ncurses.h>
#include <stdlib.h>

#define POS(X,Y)	Y * COLS + X

void init_world(bool *world);
void draw_world(bool *world);
void update_world(bool *world);
int count_neighbours(bool *world, int x, int y);
bool get_pos(bool *world, int x, int y);

int main(void)
{
	srand(time(NULL));
	initscr();
	clear();
	noecho();
	cbreak();
	curs_set(0);

	bool world[LINES * COLS];
	init_world(world);
	int ch;
	while((ch = getch()) != 'q') {
		draw_world(world);
		update_world(world);
		refresh();
	}

	clrtoeol();
	refresh();
	endwin();

	return 0;
}

void init_world(bool *world)
{
	int y, x;
	for(y = 0; y < LINES; y++)
		for(x = 0; x < COLS; x++)
			world[POS(x,y)] = rand() % 2;
}

void draw_world(bool *world)
{
	int y, x;
	for(y = 0; y < LINES; y++) {
		for(x = 0; x < COLS; x++) {
			if(world[POS(x, y)])
				mvprintw(y, x, "%d", world[POS(x, y)]);
			else
				mvprintw(y, x, " ");
		}
	}
}

void update_world(bool *world)
{
	bool new_world[LINES * COLS];
	int y, x;
	for(y = 0; y < LINES; y++) {
		for(x = 0; x < COLS; x++) {
			int neighbours = count_neighbours(world, x, y);
			new_world[POS(x, y)] = neighbours == 2 && world[POS(x, y)]
				|| neighbours == 3;
		}
	}

	for(y = 0; y < LINES; y++)
		for(x = 0; x < COLS; x++)
			world[POS(x, y)] = new_world[POS(x, y)];
}

int count_neighbours(bool *world, int x, int y)
{
	int r = get_pos(world, x-1, y-1) +
		get_pos(world, x, y-1) +
		get_pos(world, x+1, y-1) +
		get_pos(world, x-1, y) +
		get_pos(world, x+1, y) +
		get_pos(world, x-1, y+1) +
		get_pos(world, x, y+1) +
		get_pos(world, x+1, y+1); 
	return r;
}

bool get_pos(bool *world, int x, int y)
{
	return world[POS(x,y)];
}
