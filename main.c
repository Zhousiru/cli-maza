#include "generator.c"
#include "renderer.c"
#include "interaction.c"
#include <stdlib.h>
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    MazeMap *mazeMap = NULL;

menu:
    clear();
    if (mazeMap != NULL)
    {
        free(mazeMap->data);
        free(mazeMap);
    }

    for (;;)
    {
        renderMenu();

        int jumpOut = 0;
        for (;;)
        {
            int ret = applyPlayerInput(NULL);

            switch (ret)
            {
            case EASY:
                mazeMap = createMazeMap(17);
                genMaze(mazeMap);
                jumpOut = 1;
                break;

            case NORMAL:
                mazeMap = createMazeMap(37);
                genMaze(mazeMap);
                jumpOut = 1;
                break;

            case HARD:
                mazeMap = createMazeMap(57);
                genMaze(mazeMap);
                jumpOut = 1;
                break;
            }

            if (jumpOut)
            {
                break;
            }
        }
        if (jumpOut)
        {
            break;
        }
    }

    clear();
    unsigned long startTime = time(NULL);

    for (;;)
    {
        setCursor(0, 0);
        renderMazeMap(mazeMap);
        renderTimer(mazeMap->size * 2 + 2, time(NULL) - startTime);
        renderToolbar(mazeMap->size * 2 + 2);

        for (;;)
        {
            int ret = applyPlayerInput(mazeMap);
            int refresh = 0;

            switch (ret)
            {
            case WIN:
                system("@cls||clear");
                break;

            case MOVE:
                refresh = 1;
                break;

            case BACK:
                goto menu;
            }

            if (refresh)
            {
                break;
            }
        }
    }
}
