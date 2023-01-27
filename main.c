#include <curses.h>
#include <stdlib.h>

typedef struct Player
{
    int xPosition;
    int yPosition;
    int health;
} Player;

int mapSetup();
int screenSetup();
Player *playerSetup();
int handleInput(int input, Player* user);
int playerMove(int x, int y, Player* user);

int main()
{
    Player *user;
    int ch;
    screenSetup();

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
    printw("Hello world!");
    noecho();
    refresh();

    return 0;
}

int mapSetup()
{
    mvprintw(13, 13, "--------");
    mvprintw(14, 13, "|......|");
    mvprintw(15, 13, "|......|");
    mvprintw(16, 13, "|......|");
    mvprintw(17, 13, "|......|");
    mvprintw(18, 13, "--------");

    mvprintw(2, 40, "--------");
    mvprintw(3, 40, "|......|");
    mvprintw(4, 40, "|......|");
    mvprintw(5, 40, "|......|");
    mvprintw(6, 40, "|......|");
    mvprintw(7, 40, "--------");

    mvprintw(10, 40, "------------");
    mvprintw(11, 40, "|..........|");
    mvprintw(12, 40, "|..........|");
    mvprintw(13, 40, "|..........|");
    mvprintw(14, 40, "|..........|");
    mvprintw(15, 40, "------------");
}

Player* playerSetup()
{
    Player* newPlayer;
    newPlayer = malloc(sizeof(Player));

    newPlayer->xPosition = 14;
    newPlayer->yPosition = 14;
    newPlayer->health = 20;

    mvprintw(newPlayer->xPosition, newPlayer->yPosition, "@");
    move(newPlayer->xPosition, newPlayer->yPosition);

    return newPlayer;
}

int handleInput(int input, Player* user)
{
    switch (input) 
    {
        /* move up */
        case 'w':
        case 'W':
            playerMove(user->xPosition - 1, user->yPosition, user);
            break;

        /* move left */
        case 'a':
        case 'A':
            playerMove(user->xPosition, user->yPosition - 1, user);
            break;

        /* move down*/
        case 's':
        case 'S':
            playerMove(user->xPosition + 1, user->yPosition, user);
            break;

        /* move right */
        case 'd':
        case 'D':
            playerMove(user->xPosition, user->yPosition + 1, user);
            break;

        default:
            break;
    }
}

int playerMove(int x, int y, Player* user)
{
    mvprintw(user->xPosition, user->yPosition, ".");

    user->xPosition = x;
    user->yPosition = y;

    mvprintw(user->xPosition, user->yPosition, "@");
    move(user->xPosition, user->yPosition); 
}
