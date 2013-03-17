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
	init_pair(2, COLOR_GREEN, COLOR_BLUE);
	init_params();

	bool world[_num_cells];
	init_world(world);
	int ch;
	while((ch = getch()) != 'q') {
		clock_t start = clock();
		
		if(ch == 'r')
			init_world(world);

		show_info(world);
		attron(COLOR_PAIR(1));
		draw_world(world);
		attroff(COLOR_PAIR(1));
		update_world(world);
		refresh();
		lock_fps(start, 30);
	}

	clrtoeol();
	endwin();

	return 0;
}

void init_params(void)
{
	getmaxyx(stdscr, _height, _width);
	_height -= 2;
	_num_cells = _height * _width;
}

void lock_fps(clock_t start, int fps)
{
	struct timespec delay;
	delay.tv_sec = 0;
	delay.tv_nsec = 1000000000/fps - (clock() - start) * 1000000000 / CLOCKS_PER_SEC;
	nanosleep(&delay, NULL);
}

void show_info(const bool *world)
{
	int num_alive = 0, n;
	for(n = 0; n < _num_cells; n++)
		num_alive += world[n];

	attron(COLOR_PAIR(2) | A_BOLD);
	mvprintw(LINES - 1, 2, "  Press q to exit  ");
	mvprintw(LINES - 1, (_width - 17) / 2, "  Cells alive: %d  ", num_alive);
	mvprintw(LINES - 1, _width - 21, "  Press r to reset  ");
	attroff(COLOR_PAIR(2) | A_BOLD);
}

void init_world(bool *world)
{
	int n;
	for(n = 0; n < _num_cells; n++)
		world[n] = rand() % 2;
}

void draw_world(const bool *world)
{
	char chars[2] = {' ', 'O'};
	int n;
	move(0,0);
	for(n = 0; n < _num_cells; n++)
		printw("%c", chars[world[n]]);
}

void update_world(bool *world)
{
	bool new_world[_num_cells];
	int y, x;
	for(y = 0; y < _height; y++) {
		for(x = 0; x < _width; x++) {
			int neighbours = count_neighbours(world, x, y);
			new_world[POS(x, y)] = neighbours == 2 && world[POS(x, y)]
				|| neighbours == 3;
		}
	}

	int n;
	for(n = 0; n < _num_cells; n++)
		world[n] = new_world[n];
}

int count_neighbours(const bool *world, const int x, const int y)
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

bool get_cell(const bool *world, const int x, const int y)
{
	return world[POS(x, y)];
}

