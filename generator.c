#ifndef GENERATOR_C
#define GENERATOR_C

#include <stdlib.h>
#include <time.h>
#include "defs.c"

typedef struct
{
    int **data;
    int size;
    int playerX;
    int playerY;
} MazeMap;

MazeMap *createMazeMap(int size);
void genMaze(MazeMap *map);
void prim(int **mazeMap, int size);

MazeMap *createMazeMap(int size)
{
    MazeMap *map = (MazeMap *)malloc(sizeof(MazeMap));

    int **data = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        data[i] = (int *)malloc(size * sizeof(int));
    }

    map->data = data;
    map->size = size;
    map->playerX = 0;
    map->playerY = 1;

    return map;
}

void genMaze(MazeMap *map)
{
    prim(map->data, map->size);
    map->data[map->playerY][map->playerX] = PLAYER;
    map->data[map->size - 2][map->size - 1] = FIN;
}

void prim(int **mazeMap, int size)
{
    int widthLimit = size - 1;
    int heightLimit = size - 1;

    // 邻墙列表
    int **blockPos = (int **)malloc(sizeof(int *) * widthLimit * heightLimit);
    int blockCount = 0;

    srand((unsigned int)time(NULL));

    // 产生空白迷宫
    for (int x = 0; x <= widthLimit; x++)
    {
        for (int y = 0; y <= heightLimit; y++)
        {
            mazeMap[x][y] = WALL;
        }
    }
    widthLimit--;
    heightLimit--;

    // 将起点作为目标格
    int targetX = 1, targetY = 1;
    // 将起点标记为通路
    mazeMap[targetX][targetY] = PATH;

    // 记录邻墙
    if (targetY > 1)
    {
        blockPos[blockCount] = (int *)malloc(sizeof(int) * 3);
        blockPos[blockCount][0] = targetX;
        blockPos[blockCount][1] = targetY - 1;
        blockPos[blockCount][2] = 0;
        blockCount++;
    }
    if (targetX < widthLimit - 1)
    {
        blockPos[blockCount] = (int *)malloc(sizeof(int) * 3);
        blockPos[blockCount][0] = targetX + 1;
        blockPos[blockCount][1] = targetY;
        blockPos[blockCount][2] = 1;
        blockCount++;
    }
    if (targetY < heightLimit - 1)
    {
        blockPos[blockCount] = (int *)malloc(sizeof(int) * 3);
        blockPos[blockCount][0] = targetX;
        blockPos[blockCount][1] = targetY + 1;
        blockPos[blockCount][2] = 2;
        blockCount++;
    }
    if (targetX > 1)
    {
        blockPos[blockCount] = (int *)malloc(sizeof(int) * 3);
        blockPos[blockCount][0] = targetX - 1;
        blockPos[blockCount][1] = targetY;
        blockPos[blockCount][2] = 3;
        blockCount++;
    }

    while (blockCount > 0)
    {
        // 随机选一堵墙
        int blockIndex = rand() % blockCount;
        // 找到墙对面的墙
        if (blockPos[blockIndex][2] == 0)
        {
            targetX = blockPos[blockIndex][0];
            targetY = blockPos[blockIndex][1] - 1;
        }
        else if (blockPos[blockIndex][2] == 1)
        {
            targetX = blockPos[blockIndex][0] + 1;
            targetY = blockPos[blockIndex][1];
        }
        else if (blockPos[blockIndex][2] == 2)
        {
            targetX = blockPos[blockIndex][0];
            targetY = blockPos[blockIndex][1] + 1;
        }
        else if (blockPos[blockIndex][2] == 3)
        {
            targetX = blockPos[blockIndex][0] - 1;
            targetY = blockPos[blockIndex][1];
        }

        // 如果目标格未连通
        if (mazeMap[targetX][targetY] == WALL)
        {
            // 联通目标格
            mazeMap[blockPos[blockIndex][0]][blockPos[blockIndex][1]] = PATH;
            mazeMap[targetX][targetY] = PATH;

            // 添加目标格相邻格
            if (targetY > 1 && mazeMap[targetX][targetY - 1] == WALL && mazeMap[targetX][targetY - 2] == WALL)
            {
                blockPos[blockCount] = (int *)malloc(sizeof(int) * 3);
                blockPos[blockCount][0] = targetX;
                blockPos[blockCount][1] = targetY - 1;
                blockPos[blockCount][2] = 0;
                blockCount++;
            }
            if (targetX < widthLimit - 1 && mazeMap[targetX + 1][targetY] == WALL && mazeMap[targetX + 2][targetY] == WALL)
            {
                blockPos[blockCount] = (int *)malloc(sizeof(int) * 3);
                blockPos[blockCount][0] = targetX + 1;
                blockPos[blockCount][1] = targetY;
                blockPos[blockCount][2] = 1;
                blockCount++;
            }
            if (targetY < heightLimit - 1 && mazeMap[targetX][targetY + 1] == WALL && mazeMap[targetX][targetY + 2] == WALL)
            {
                blockPos[blockCount] = (int *)malloc(sizeof(int) * 3);
                blockPos[blockCount][0] = targetX;
                blockPos[blockCount][1] = targetY + 1;
                blockPos[blockCount][2] = 2;
                blockCount++;
            }
            if (targetX > 1 && mazeMap[targetX - 1][targetY] == WALL && mazeMap[targetX - 2][targetY] == WALL)
            {
                blockPos[blockCount] = (int *)malloc(sizeof(int) * 3);
                blockPos[blockCount][0] = targetX - 1;
                blockPos[blockCount][1] = targetY;
                blockPos[blockCount][2] = 3;
                blockCount++;
            }
        }

        free(blockPos[blockIndex]);

        blockCount--;
        blockPos[blockIndex] = blockPos[blockCount];
    }

    free(blockPos);
}

#endif
