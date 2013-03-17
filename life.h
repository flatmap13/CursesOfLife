#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define POS(X,Y)	Y * _width + X

void init_params(void);
void show_info(const bool *world);
void init_world(bool *world);
void draw_world(const bool *world);
void update_world(bool *world);
int count_neightbours(const bool *world, const int x, const int y);
bool get_cell(const bool *world, const int x, const int y);

static int _width;
static int _height;
static int _num_cells;

