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

Grid *__new__Grid(int, int);
void update(Grid*);
void display(Grid*);
void __del__Grid(Grid*);

#endif
