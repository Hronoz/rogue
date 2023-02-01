#include <curses.h>
#include <stdlib.h>
#include <time.h>

typedef struct Position
{
    int x;
    int y;
    /* TILE_TYPE tile; */
} Position;

typedef struct Room
{
    Position position;
    int height;
    int width;
    Position door[4];
    /* TODO: Struct of monsters
       TODO: Struct of items */ 
} Room;

typedef struct Player
{
    Position position;
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
    newRoom->position.y = y;
    newRoom->position.x = x;
    newRoom->height = height;
    newRoom->width = width;

    /* top door */
    newRoom->door[0].x = rand() % (width - 2) + newRoom->position.x + 1;
    newRoom->door[0].y = newRoom->position.y;

    /* bottom door */
    newRoom->door[1].x = rand() % (width - 2) + newRoom->position.x + 1;
    newRoom->door[1].y = newRoom->position.y + newRoom->height - 1;

    /* left door */
    newRoom->door[2].x = newRoom->position.x;
    newRoom->door[2].y = rand() % (height - 2) + newRoom->position.y + 1;

    /* rigth door */
    newRoom->door[3].x = newRoom->position.x + newRoom->width - 1;
    newRoom->door[3].y = rand() % (height - 2) + newRoom->position.y + 1;

    return newRoom;
}

int drawRoom(Room* room)
{
    int y;
    int x;

    /* draw top and bottom */
    for (x = room->position.x; x < room->position.x + room->width; x++)
    {
        mvprintw(room->position.y, x, "-");
        mvprintw(room->position.y + room->height - 1, x, "-");
    }
    /* draw left and rigth sides of room and fill the room
     * with empty space */
    for (y = room->position.y + 1;
         y < room->position.y + room->height - 1;
         y++)
    {
        mvprintw(y, room->position.x, "|"); /* left */

        /* fill the room with empty space */
        for (x = room->position.x + 1;
             x < room->position.x + room->width- 1;
             x++)
        {
            mvprintw(y, x, ".");
        }

        mvprintw(y, room->position.x + room->width - 1, "|"); /* right */
    }

    /* draw doors */
    mvprintw(room->door[0].y, room->door[0].x, "+");
    mvprintw(room->door[1].y, room->door[1].x, "+");
    mvprintw(room->door[2].y, room->door[2].x, "+");
    mvprintw(room->door[3].y, room->door[3].x, "+");
    return 0;
}

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
        /* move up */
        case 'w':
        case 'W':
            destinationY = user->position.y - 1;
            destinationX = user->position.x;
            break;
        /* move left */
        case 'a':
        case 'A':
            destinationY = user->position.y;
            destinationX = user->position.x - 1;
            break;
        /* move down*/
        case 's':
        case 'S':
            destinationY = user->position.y + 1;
            destinationX = user->position.x;
            break;
        /* move right */
        case 'd':
        case 'D':
            destinationY = user->position.y;
            destinationX = user->position.x + 1;
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
