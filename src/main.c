#include <stdlib.h>
#include <time.h>
#include "rogue.h"


int main()
{
    Player *user;
    char **level;
    int ch;

    screenSetup();
    srand(time(NULL));

    mapSetup();

    user = playerSetup();

    /* main game loop */
    while ((ch = getch()) != 'q') 
    {
        handleInput(ch, user);
    }

    endwin();

    return 0;
}

int screenSetup()
{
    initscr();
    noecho();

    return 0;
}

