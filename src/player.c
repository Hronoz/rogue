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

int handleInput(int input, Player* user)
{
    int destinationY, destinationX;
    switch (input) 
    {
        /* move right */
        case 'l':
            destinationY = user->position.y;
            destinationX = user->position.x + 1;
            break;
        /* move up */
        case 'k':
            destinationY = user->position.y - 1;
            destinationX = user->position.x;
            break;
        /* move left */
        case 'h':
            destinationY = user->position.y;
            destinationX = user->position.x - 1;
            break;
        /* move down*/
        case 'j':
            destinationY = user->position.y + 1;
            destinationX = user->position.x;
            break;
        default:
            break;
    }

    checkPostion(destinationY, destinationX, user);
    return 0;
}

/* check what is at next position */
int checkPostion(int destinationY, int destinationX, Player* user)
{
    switch (mvinch(destinationY, destinationX)) {
        case '.':
        case '#':
        case '+':
            playerMove(destinationY, destinationX, user);
            break;
        default:
            move(user->position.y, user->position.x);
            break;
    }
    return 0;
}

int playerMove(int y, int x, Player* user)
{
    mvprintw(user->position.y, user->position.x, ".");

    user->position.y = y;
    user->position.x = x;

    mvprintw(user->position.y, user->position.x, "@");
    move(user->position.y, user->position.x); 
    return 0;
}
