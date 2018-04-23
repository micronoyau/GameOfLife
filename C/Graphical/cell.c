#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "cell.h"

const int CELL_SIZE = 15;

const char CELL_ALIVE_R = 200;
const char CELL_ALIVE_G = 128;
const char CELL_ALIVE_B = 0;
const char CELL_DEAD_R = 0;
const char CELL_DEAD_G = 0;
const char CELL_DEAD_B = 0;

// Règles
const char KEEPALIVE_CELL_NEIGHBOURS[] = {2,3};
const char BORN_CELL_NEIGHBOURS[] = {3};

Cell *__new__Cell(int x, int y, char state)
{
    Cell *cell = malloc(sizeof(*cell));
    cell->pos[0] = x;
    cell->pos[1] = y;
    cell->state = state;
    cell->total_neighbours = 0;
    return cell;
}

void evol(Cell *cell, Cell *neighbours[8])
{
    int i;
    cell->total_neighbours = 0;
    for(i=0; i<8; i++)
    {
        if( neighbours[i]->state == CELL_ALIVE )
        {
            cell->total_neighbours++;
        }
    }
}

void redraw(Cell *cell)
{
    int i;
    if( cell->state == CELL_ALIVE )
    {
        cell->state = CELL_DEAD;
        for(i=0; i<sizeof(KEEPALIVE_CELL_NEIGHBOURS); i++)
        {
            if( cell->total_neighbours == KEEPALIVE_CELL_NEIGHBOURS[i] )
            {
                cell->state = CELL_ALIVE;
                break;
            }
        }
    }
    else{
        for(i=0; i<sizeof(BORN_CELL_NEIGHBOURS); i++)
        {
            if( cell->total_neighbours == BORN_CELL_NEIGHBOURS[i] )
            {
                cell->state = CELL_ALIVE;
                break;
            }
        }
    }
    /*
    //Old method
    if( cell->state == CELL_ALIVE && (cell->total_neighbours < 2 || cell->total_neighbours > 3) )
    {
        cell->state = CELL_DEAD;
    }
    else if( cell->state == CELL_DEAD && cell->total_neighbours == 3 ){
        cell->state = CELL_ALIVE;
    }
    */
}
