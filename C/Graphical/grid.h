#ifndef GRID_H
#define GRID_H

#include "cell.h"

typedef struct Grid
{
    Cell ***array;
    int width;
    int height;
    int gen;
} Grid;

Grid *__new__Grid(int width, int height);
void emptyGrid(Grid *grid);
void updateGrid(Grid* grid);
void changeGridCell(Grid *grid, int x, int y, char state);
void displayGrid(Grid* grid, SDL_Surface* screen);
void __del__Grid(Grid* grid);

#endif
