#include <stdio.h>
#include <stdlib.h>

char ALIVE = 'o';
char DEAD = ' ';

typedef struct Cell                                                                                                                                                             
{                                                                                                                                                                               
    int pos[2];                                                                                                                                                                 
    char img;                                                                                                                                                                   
    int total_neighbours;                                                                                                                                                       
} Cell;                                                                                                                                                                         

Cell *__new__Cell(int x, int y, char img)
{
    Cell *cell = malloc(sizeof(*cell));
    cell->pos[0] = x;
    cell->pos[1] = y;
    cell->img = img;
    cell->total_neighbours = 0;
    return cell;
}

void evol(Cell *cell, Cell *neighbours[8])
{
    int i;
    cell->total_neighbours = 0;
    for(i=0; i<8; i++){
        if( neighbours[i]->img == ALIVE ){
            cell->total_neighbours++;
        }
    }
}

void redraw(Cell *cell)
{
    // Mort
    if( cell->img == ALIVE && (cell->total_neighbours < 2 || cell->total_neighbours > 3) ){
        cell->img = DEAD;
    }
    // Naissance
    else if( cell->img == DEAD && cell->total_neighbours == 3 ){
        cell->img = ALIVE;
    }
    // Sinon on garde l'état initial
}
