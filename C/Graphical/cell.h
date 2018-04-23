#ifndef CELL_H
#define CELL_H

#define CELL_ALIVE 1
#define CELL_DEAD 0

extern const int CELL_SIZE;

extern const char CELL_ALIVE_R;
extern const char CELL_ALIVE_G;
extern const char CELL_ALIVE_B;
extern const char CELL_DEAD_R;
extern const char CELL_DEAD_G;
extern const char CELL_DEAD_B;

typedef struct Cell
{
    int pos[2];
    char state;
    char total_neighbours;
} Cell;

Cell *__new__Cell(int x, int y, char state);
void evol(Cell* cell, Cell* neighbours[8]);
void redraw(Cell* cell);

#endif
