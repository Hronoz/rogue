#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>

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
    Position **doors;
    /* TODO: Struct of monsters
       TODO: Struct of items */ 
} Room;

typedef struct Player
{
    Position position;
    int health;
} Player;

int screenSetup();

/* level/map function */
char** mapSetup();

/* player functions */
Player* playerSetup();
int handleInput(int input, Player* user);
int playerMove(int y, int x, Player* user);
int checkPostion(int destinationY, int destinationX, Player* user);

/* room functions */
Room* createRoom(int y, int x, int height, int width);
int drawRoom(Room* room);
int connectDoors(Position *doorOne, Position *doorTwo);

#endif
