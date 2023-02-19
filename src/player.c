#include <stdio.h>
#include <stdlib.h>
#include "rogue.h"


Player* playerSetup()
{
    Player* newPlayer;
    newPlayer = malloc(sizeof(Player));

    newPlayer->position.x = 14;
    newPlayer->position.y = 14;
    newPlayer->health = 20;

    mvprintw(newPlayer->position.y, newPlayer->position.x, "@");
    move(newPlayer->position.y, newPlayer->position.x);

    return newPlayer;
}

Position* handleInput(int input, Player* user)
{
    Position *newPosition;
    newPosition = malloc(sizeof(Position));
    switch (input) 
    {
        /* move right */
        case 'l':
            newPosition->y = user->position.y;
            newPosition->x = user->position.x + 1;
            break;
        /* move up */
        case 'k':
            newPosition->y = user->position.y - 1;
            newPosition->x = user->position.x;
            break;
        /* move left */
        case 'h':
            newPosition->y = user->position.y;
            newPosition->x = user->position.x - 1;
            break;
        /* move down*/
        case 'j':
            newPosition->y = user->position.y + 1;
            newPosition->x = user->position.x;
            break;
        default:
            break;
    }

    return newPosition;
}

/* check what is at next position */
int checkPostion(Position *newPosition, Player* user, char **level)
{
    switch (mvinch(newPosition->y, newPosition->x)) {
        case '.':
        case '#':
        case '+':
            playerMove(newPosition, user, level);
            break;
        default:
            break;
    }
    return 0;
}

int playerMove(Position *newPosition, Player* user, char **level)
{
    char buffer[8];

    /* conerting the single character to string */
    sprintf(buffer, "%c",level[user->position.y][user->position.x]);

    mvprintw(user->position.y, user->position.x, "%s", buffer);

    user->position.y = newPosition->y;
    user->position.x = newPosition->x;

    mvprintw(user->position.y, user->position.x, "@");
    move(user->position.y, user->position.x); 
    return 0;
}
