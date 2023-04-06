#ifndef INTERACTION_C
#define INTERACTION_C

#include "defs.c"
#include "generator.c"
#include <conio.h>

int move(MazeMap *map, int y, int x);

int applyPlayerInput(MazeMap *map)
{
    switch (getch())
    {
    case 'D':
    case 'd':
        if (map != NULL)
        {
            return move(map, 0, 1);
        }

        break;

    case 'A':
    case 'a':
        if (map != NULL)
        {
            return move(map, 0, -1);
        }
        break;

    case 'W':
    case 'w':
        if (map != NULL)
        {
            return move(map, -1, 0);
        }
        break;

    case 'S':
    case 's':
        if (map != NULL)
        {
            return move(map, 1, 0);
        }
        break;

    case 'Q':
    case 'q':
        return BACK;
        break;

    case '1':
        return EASY;
        break;

    case '2':
        return NORMAL;
        break;

    case '3':
        return HARD;
        break;

    case '4':
        return LIST;
        break;
    }
}

int move(MazeMap *map, int y, int x)
{
    int newPos[2] = {map->playerY + y,
                     map->playerX + x};

    if (newPos[0] < 0 || newPos[1] < 0 || newPos[0] > map->size - 1 || newPos[1] > map->size - 1)
    {
        return INVALID;
    }

    if (map->data[newPos[0]][newPos[1]] == WALL)
    {
        return INVALID;
    }

    if (map->data[newPos[0]][newPos[1]] == FIN)
    {
        return WIN;
    }

    (map->data)[map->playerY][map->playerX] = PATH;
    (map->data)[newPos[0]][newPos[1]] = PLAYER;
    map->playerY = newPos[0];
    map->playerX = newPos[1];

    return MOVE;
}

#endif
