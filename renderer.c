#ifndef RENDERER_C
#define RENDERER_C

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "defs.c"

const char SYMBOL_WALL[] = "🧱";
const char SYMBOL_PATH[] = "  ";
const char SYMBOL_PLAYER[] = "😼";
const char SYMBOL_FIN[] = "🐟";

void setCursor(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void repeatCh(char *ch, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(ch);
    }
}

void renderCenter(char *str, int width)
{
    int leftPadding = (width - strlen(str)) / 2;
    int rightPadding = width - strlen(str) - leftPadding;
    repeatCh(" ", leftPadding);
    printf("%s", str);
    repeatCh(" ", rightPadding);
}

void clear()
{
    system("@cls||clear");
}

void renderMazeMap(MazeMap *map)
{
    printf("╭");
    repeatCh("─", map->size * 2);
    printf("╮\n");

    for (int i = 0; i < map->size; i++)
    {
        printf("│");
        for (int j = 0; j < map->size; j++)
        {
            switch (map->data[i][j])
            {
            case WALL:
                printf(SYMBOL_WALL);
                break;

            case PATH:
                printf(SYMBOL_PATH);
                break;

            case PLAYER:
                printf(SYMBOL_PLAYER);
                break;

            case FIN:
                printf(SYMBOL_FIN);
                break;

            default:
                break;
            }
        }
        printf("│\n");
    }

    printf("├");
    repeatCh("─", map->size * 2);
    printf("┤\n");
}

void renderTimer(int width, unsigned long secs)
{
    char str[50] = "";
    int m = secs / 60;
    int s = secs % 60;
    sprintf(str, "%02d:%02d", m, s);

    printf("│");
    renderCenter(str, width - 2);
    printf("│\n");
    printf("├");
    repeatCh("─", width - 2);
    printf("┤\n");
}

void renderToolbar(int width)
{
    printf("│ 移动：WASD");
    repeatCh(" ", width - 21);
    printf("返回：Q │\n");

    printf("╰");
    repeatCh("─", width - 2);
    printf("╯\n");
}

void renderMenu()
{
    printf("╭────────────────────────╮\n");
    printf("│                        │\n");
    printf("│      😽 简单 [1]       │\n");
    printf("│      😺 一般 [2]       │\n");
    printf("│      😾 困难 [3]       │\n");
    printf("│                        │\n");
    printf("│      🐟 排行 [4]       │\n");
    printf("│                        │\n");
    printf("╰────────────────────────╯\n");
}

void renderList()
{
    printf("╭────────────────────────╮\n");
    printf("│          排行榜         │\n");
    printf("├────────────────────────┤\n");
    printf("│      简单       │\n");
    printf("╰────────────────────────╯\n");
}

#endif
