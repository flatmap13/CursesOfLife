#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define WIDTH		COLS
#define HEIGHT		LINES - 2
#define NUM_CELLS	WIDTH * HEIGHT
#define POS(X,Y)	Y * COLS + X

void show_info(const bool *world);
void init_world(bool *world);
void draw_world(const bool *world);
void update_world(bool *world);
int count_neightbours(const bool *world, const int x, const int y);
bool get_cell(const bool *world, const int x, const int y);

