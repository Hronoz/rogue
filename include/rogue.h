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
Room** mapSetup();
char** saveLevelPositions();

/* player functions */
Player* playerSetup();
Position* handleInput(int input, Player* user);
int playerMove(Position *newPosition, Player* user, char **level);
int checkPostion(Position *newPosition, Player* user, char **level);

/* room functions */
Room* createRoom(int y, int x, int height, int width);
int drawRoom(Room* room);
int connectDoors(Position *doorOne, Position *doorTwo);

#endif
