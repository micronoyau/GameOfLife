#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "time.h"
#include "grid.h"

Grid *grid;
int cont = 1;

void clearMem(int signum)
{
    __del__Grid(grid);
    cont = 0;
}

int main(void)
{
    grid = __new__Grid(150,36);
    signal(SIGINT, clearMem);
    while(cont==1){
        system("clear");
        update(grid);
        printf("GENERATION %d\n", grid->gen);
        display(grid);
        const struct timespec t = {0, 50000000};
        nanosleep(&t, NULL);
    }
    return 0;
}
