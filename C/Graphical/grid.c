#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include "grid.h"
#include "cell.h"

static const char START_GEN_RAND = 1;

int getRand()
{
    return rand()%2;
}

void genGrid(Grid *grid)
{
    int x;
    int y;
    for(y=0; y<grid->height; y++)
    {
        for(x=0; x<grid->width; x++)
        {
            if( getRand() == 0 )
            {
                grid->array[y][x]->state = CELL_DEAD;
            }
            else{
                grid->array[y][x]->state = CELL_ALIVE;
            }
        }
    }
}

Grid *__new__Grid(int width, int height)
{
    Grid *grid = malloc(sizeof(*grid));
    grid->width = width;
    grid->height = height;
    grid->array = malloc(sizeof(int*)*grid->height);
    grid->gen = 0;

    int x,y;
    for(y=0; y<grid->height; y++)
    {
        grid->array[y] = malloc(sizeof(int*)*grid->width);
        for(x=0; x<grid->width; x++)
        {
            grid->array[y][x] = __new__Cell(x, y, CELL_DEAD);
        }
    }
    srand(time(NULL));
    
    if( START_GEN_RAND == 1 )
    {
        genGrid(grid);
    }

    return grid;
}

void emptyGrid(Grid *grid)
{
    int x,y;
    for(y=0; y<grid->height; y++)
    {
        for(x=0; x<grid->width; x++)
        {
            grid->array[y][x]->state = CELL_DEAD;
        }
    }
}

void changeGridCell(Grid *grid, int x, int y, char state)
{
    Cell *cell = grid->array[y%grid->height][x%grid->width];
    cell->state = state;
}

void updateGrid(Grid *grid)
{
    int x,y;
    for(y=0; y<grid->height; y++)
    {
        for(x=0; x<grid->width; x++)
        {
            Cell *neighbours[8] = { grid->array[(y-1+grid->height)%grid->height][(x-1+grid->width)%grid->width],
                                    grid->array[y][(x-1+grid->width)%grid->width],
                                    grid->array[(y+1)%grid->height][(x-1+grid->width)%grid->width],
                                    grid->array[(y-1+grid->height)%grid->height][x],
                                    grid->array[(y+1)%grid->height][x],
                                    grid->array[(y-1+grid->height)%grid->height][(x+1)%grid->width],
                                    grid->array[y][(x+1)%grid->width],
                                    grid->array[(y+1)%grid->height][(x+1)%grid->width] };
            evol( grid->array[y][x], neighbours );
        }
    }
    for(y=0; y<grid->height; y++)
    {
        for(x=0; x<grid->width; x++)
        {
            redraw(grid->array[y][x]);
        }
    }
    grid->gen++;
}

void displayGrid(Grid *grid, SDL_Surface *screen)
{
    SDL_Surface *dead = SDL_CreateRGBSurface(SDL_HWSURFACE, CELL_SIZE, CELL_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(dead, NULL, SDL_MapRGB(screen->format, CELL_DEAD_R, CELL_DEAD_G, CELL_DEAD_B));
    SDL_Surface *alive = SDL_CreateRGBSurface(SDL_HWSURFACE, CELL_SIZE, CELL_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(alive, NULL, SDL_MapRGB(screen->format, CELL_ALIVE_R, CELL_ALIVE_G, CELL_ALIVE_B));
    SDL_Rect pos;

    int x,y;
    for(y=0; y<grid->height; y++)
    {
        for(x=0; x<grid->width; x++)
        {
            pos.x = x*CELL_SIZE;
            pos.y = y*CELL_SIZE;
            if( grid->array[y][x]->state == CELL_ALIVE )
            {
                SDL_BlitSurface(alive, NULL, screen, &pos);
            }
            else{
                SDL_BlitSurface(dead, NULL, screen, &pos);
            }
        }
    }

    SDL_FreeSurface(dead);
    SDL_FreeSurface(alive);
    SDL_Flip(screen);
}

void __del__Grid(Grid *grid)
{
    int x,y;
    for(y=0; y<grid->height; y++)
    {
        for(x=0; x<grid->width; x++)
        {
            free(grid->array[y][x]);
        }
        free(grid->array[y]);
    }
    free(grid);
}
