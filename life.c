#include "life.h"

int main(void)
{
	srand(time(NULL));
	initscr();
	clear();
	noecho();
	cbreak();
	curs_set(0);
	nodelay(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	show_info();

	bool world[NUM_CELLS];
	init_world(world);
	int ch;
	while((ch = getch()) != 'q') {
		clock_t start = clock();

		attron(COLOR_PAIR(1));
		draw_world(world);
		attroff(COLOR_PAIR(1));
		update_world(world);
		refresh();

		while((clock() - start) * 1000 / CLOCKS_PER_SEC < 1000/30);
	}

	clrtoeol();
	refresh();
	endwin();

	return 0;
}

void show_info(void) {
	attron(COLOR_PAIR(2) | A_BOLD);
	mvprintw(LINES - 1, 3, " Press q to exit ");
	attroff(COLOR_PAIR(2) | A_BOLD);
}

void init_world(bool *world)
{
	int n;
	for(n = 0; n < NUM_CELLS; n++)
		world[n] = rand() % 2;
}

void draw_world(bool *world)
{
	char chars[2] = {' ', 'O'};
	int y, x;
	for(y = 0; y < HEIGHT; y++)
		for(x = 0; x < WIDTH; x++)
			mvprintw(y, x, "%c", chars[world[POS(x, y)]]);
}

void update_world(bool *world)
{
	bool new_world[NUM_CELLS];
	int y, x;
	for(y = 0; y < HEIGHT; y++) {
		for(x = 0; x < WIDTH; x++) {
			int neighbours = count_neighbours(world, x, y);
			new_world[POS(x, y)] = neighbours == 2 && world[POS(x, y)]
				|| neighbours == 3;
		}
	}

	int n;
	for(n = 0; n < NUM_CELLS; n++)
		world[n] = new_world[n];
}

int count_neighbours(bool *world, int x, int y)
{
	return get_cell(world, x-1, y-1) +
		get_cell(world, x, y-1) +
		get_cell(world, x+1, y-1) +
		get_cell(world, x-1, y) +
		get_cell(world, x+1, y) +
		get_cell(world, x-1, y+1) +
		get_cell(world, x, y+1) +
		get_cell(world, x+1, y+1); 
}

bool get_cell(bool *world, int x, int y)
{
	return world[POS(x,y)];
}
