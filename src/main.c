#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "rogue.h"


int main()
{
    Player *user;
    Position *newPosition;
    char **level;
    int ch;

    screenSetup();
    srand(time(NULL));

    mapSetup();

    level = saveLevelPositions();

    user = playerSetup();

    /* main game loop */
    while ((ch = getch()) != 'q') 
    {
        newPosition = handleInput(ch, user);
        checkPostion(newPosition, user, level);
    }

    endwin();

    return 0;
}

int screenSetup()
{
    initscr();
    noecho();
    curs_set(0);

    return 0;
}

