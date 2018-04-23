#ifndef CELL_H
#define CELL_H

extern char ALIVE;
extern char DEAD;

typedef struct Cell
{
    int pos[2];
    char img;
    int total_neighbours;
} Cell;

Cell *__new__Cell(int, int, char);
void evol(Cell*, Cell* neighbours[8]);
void redraw(Cell*);

#endif
