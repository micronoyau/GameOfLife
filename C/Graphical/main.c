/*
 * Jeu de la vie de Conway en C.
 * Dépendance : SDL v1.2
 * @DonKey
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <SDL/SDL.h>
#include <time.h>
#include "grid.h"
#include "cell.h"

static const int SCREEN_WIDTH = 1550;
static const int SCREEN_HEIGHT = 750;

static const float T_SLEEP = 0.01; // En s et <1s
static const char FULLSCREEN = 0;

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *screen;
    if( FULLSCREEN )
    {
        screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_FULLSCREEN);
    }
    else{
        screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE);
    }
    if( screen == NULL )
    {
        fprintf(stderr, "%s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Game of life", NULL);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    Grid *grid = __new__Grid(SCREEN_WIDTH/CELL_SIZE, SCREEN_HEIGHT/CELL_SIZE);

    SDL_Event event;
    char pause = 0;
    int clicked = 0;
    int cont = 1;
    while(cont)
    {
        while( SDL_PollEvent(&event) != 0 )
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    cont = 0;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if( event.button.button == SDL_BUTTON_LEFT )
                    {
                        clicked = SDL_BUTTON_LEFT;
                        changeGridCell(grid, event.button.x/CELL_SIZE, event.button.y/CELL_SIZE, CELL_ALIVE);
                    }
                    else if( event.button.button == SDL_BUTTON_RIGHT )
                    {
                        clicked = SDL_BUTTON_RIGHT;
                        changeGridCell(grid, event.button.x/CELL_SIZE, event.button.y/CELL_SIZE, CELL_DEAD);
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    clicked=0;
                    break;

                case SDL_MOUSEMOTION:
                    if( clicked == SDL_BUTTON_LEFT )
                    {
                        changeGridCell(grid, event.button.x/CELL_SIZE, event.button.y/CELL_SIZE, CELL_ALIVE);
                    }
                    else if( clicked == SDL_BUTTON_RIGHT )
                    {
                        changeGridCell(grid, event.button.x/CELL_SIZE, event.button.y/CELL_SIZE, CELL_DEAD);
                    }
                    break;

                case SDL_KEYDOWN:
                    if( event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q )
                    {
                        cont = 0;
                    }
                    else if( event.key.keysym.sym == SDLK_SPACE )
                    {
                        pause = (pause+1)%2;
                    }
                    else if( event.key.keysym.sym == SDLK_c )
                    {
                        emptyGrid(grid);
                    }
                    break;
            }
        }
        if( !pause )
        {
            updateGrid(grid);
        }
        displayGrid(grid, screen);

        const struct timespec t = {0, T_SLEEP*1000000000};
        nanosleep(&t, NULL);
    }

    __del__Grid(grid);
    SDL_Quit();
    return EXIT_SUCCESS;
}
