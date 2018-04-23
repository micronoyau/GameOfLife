#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cell.h"

typedef struct Grid
{
    Cell ***array;
    int width;
    int height;
    int gen;
} Grid;

int getRand()
{
    return rand()%2;
}

void genGrid(Grid *grid)
{
    int x;
    int y;
    for(y=0; y<grid->height; y++){
        for(x=0; x<grid->width; x++){
            if( getRand() == 0 ){
                grid->array[y][x]->img = DEAD;
            }
            else{
                grid->array[y][x]->img = ALIVE;
            }
        }
    }
}

Grid *__new__Grid(int width, int height)
{
    Grid *grid = malloc(sizeof(*grid));
    grid->width = width;
    grid->height = height;
    // La taille des pointeurs est la même pour tous les types
    grid->array = malloc(sizeof(int*)*grid->height);
    grid->gen = 0;

    int x,y;
    for(y=0; y<grid->height; y++){
        grid->array[y] = malloc(sizeof(int*)*grid->width);
        for(x=0; x<grid->width; x++){
            grid->array[y][x] = __new__Cell(x, y, DEAD);
        }
    }

    srand(time(NULL));
    genGrid(grid);

    return grid;
}

void update(Grid *grid)
{
    int x,y;
    for(y=0; y<grid->height; y++){
        for(x=0; x<grid->width; x++){
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
    for(y=0; y<grid->height; y++){
        for(x=0; x<grid->width; x++){
            redraw(grid->array[y][x]);
        }
    }
    grid->gen++;
}

void display(Grid *grid)
{
    int x,y,i;
    for(i=0; i<grid->width; i++){
        printf("_");
    }
    printf("\n");
    for(y=0; y<grid->height; y++){
        printf("|");
        for(x=0; x<grid->width; x++){
            printf("%c", grid->array[y][x]->img);
        }
        printf("|\n");
    }
    for(i=0; i<grid->width; i++){
        printf("-");
    }
    printf("\n");
}

void __del__Grid(Grid *grid)
{
    int x,y;
    for(y=0; y<grid->height; y++){
        for(x=0; x<grid->width; x++){
            free(grid->array[y][x]);
        }
        free(grid->array[y]);
    }
    free(grid);
}
