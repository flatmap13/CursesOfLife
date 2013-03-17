#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define WIDTH		COLS
#define HEIGHT		LINES - 2
#define NUM_CELLS	WIDTH * HEIGHT
#define POS(X,Y)	Y * COLS + X

void show_info(void);
void init_world(bool *world);
void draw_world(bool *world);
void update_world(bool *world);
int count_neightbours(bool *world, int x, int y);
bool get_cell(bool *world, int x, int y);

