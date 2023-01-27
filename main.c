#include <curses.h>
#include <stdlib.h>

typedef struct Room
{
    int yPosition;
    int xPosition;
    int height;
    int width;
    /* TODO: Struct of monsters
       TODO: Struct of items */ 
} Room;

typedef struct Player
{
    int yPosition;
    int xPosition;
    int health;
} Player;

int screenSetup();
Room** mapSetup();
Player *playerSetup();
int handleInput(int input, Player* user);
int playerMove(int y, int x, Player* user);
int checkPostion(int destinationY, int destinationX, Player* user);
Room* createRoom(int y, int x, int height, int width);
int drawRoom(Room* room);

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
    noecho();
    refresh();

    return 0;
}

Room** mapSetup()
{
    Room** rooms;
    rooms = malloc(sizeof(Room)*6);

    rooms[0] = createRoom(13, 13, 6, 8);
    drawRoom(rooms[0]);


    rooms[1] = createRoom(2, 40, 6, 8);
    drawRoom(rooms[1]);


    rooms[2] = createRoom(10, 40, 6, 12);
    drawRoom(rooms[2]);

    return rooms;
}

Room* createRoom(int y, int x, int height, int width)
{
    Room* newRoom;
    newRoom = malloc(sizeof(Room));

    newRoom->yPosition = y;
    newRoom->xPosition = x;
    newRoom->height = height;
    newRoom->width = width;

    return newRoom;
}

int drawRoom(Room* room)
{
    int y;
    int x;

    /* draw top and bottom */
    for (x = room->xPosition; x < room->xPosition + room->width; x++)
    {
        mvprintw(room->yPosition, x, "-");
        mvprintw(room->yPosition + room->height, x, "-");
    }
    /* draw left and rigth sides of room and fill the room
     * with empty space */
    for (y = room->yPosition + 1; y < room->yPosition + room->height; y++)
    {
        mvprintw(y, room->xPosition, "|"); /* left */

        for (x = room->xPosition + 1;
             x < room->xPosition + room->width- 1; x++)
        {
            mvprintw(y, x, ".");
        }
        mvprintw(y, room->xPosition + room->width - 1, "|"); /* right */
    }
}

Player* playerSetup()
{
    Player* newPlayer;
    newPlayer = malloc(sizeof(Player));

    newPlayer->xPosition = 14;
    newPlayer->yPosition = 14;
    newPlayer->health = 20;

    mvprintw(newPlayer->yPosition, newPlayer->xPosition, "@");
    move(newPlayer->yPosition, newPlayer->xPosition);

    return newPlayer;
}

int handleInput(int input, Player* user)
{
    int destinationY, destinationX;
    switch (input) 
    {
        /* move up */
        case 'w':
        case 'W':
            destinationY = user->yPosition - 1;
            destinationX = user->xPosition;
            break;

        /* move left */
        case 'a':
        case 'A':
            destinationY = user->yPosition;
            destinationX = user->xPosition - 1;
            break;

        /* move down*/
        case 's':
        case 'S':
            destinationY = user->yPosition + 1;
            destinationX = user->xPosition;
            break;

        /* move right */
        case 'd':
        case 'D':
            destinationY = user->yPosition;
            destinationX = user->xPosition + 1;
            break;

        default:
            break;
    }

    checkPostion(destinationY, destinationX, user);
}

/* check what is at next position */
int checkPostion(int destinationY, int destinationX, Player* user)
{
    switch (mvinch(destinationY, destinationX)) {
        case '.':
            playerMove(destinationY, destinationX, user);
            break;
        default:
            move(user->yPosition, user->xPosition);
            break;
    }
}

int playerMove(int y, int x, Player* user)
{
    mvprintw(user->yPosition, user->xPosition, ".");

    user->yPosition = y;
    user->xPosition = x;

    mvprintw(user->yPosition, user->xPosition, "@");
    move(user->yPosition, user->xPosition); 
}
