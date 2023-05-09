#include <raylib.h>
#include "src/states/state.h"
#include "src/states/ingame.h"
#include "src/states/menu.h"
#include "main.h"

#include <iostream>

inline void cToggleFullscreen(Config*);

int main(void)
{
    Config* config = new Config{ 1280,720 };
    InitWindow(1280, 720, "Demo game with raylib");

    SetTargetFPS(165);

    State *currentState = new Menu(config);

    while (!WindowShouldClose())
    {

        if (IsKeyPressed(KEY_F)) cToggleFullscreen(config);
        
        currentState->update();

        BeginDrawing();

        currentState->render();

        DrawFPS(config->windowWidth-90, 10);
        EndDrawing();

        char signal = currentState->signal();
        if (signal != -1)
        {
            switch (signal)
            {
            case 1:
                delete currentState;
                currentState = new Menu(config);
                break;
            case 2:
                delete currentState;
                currentState = new InGame(config);
                break;
            default:
                break;
            }
        }
    }

    delete currentState;

    CloseWindow();

    return 0;
}


inline void cToggleFullscreen(Config *config) {
    if (IsWindowFullscreen())
    {
        config->windowHeight = 720;
        config->windowWidth = 1280;
        ToggleFullscreen();
        SetWindowSize(config->windowWidth, config->windowHeight);
    }
    else
    {
        int monitor = GetCurrentMonitor();
        config->windowHeight = GetMonitorHeight(monitor);
        config->windowWidth = GetMonitorWidth(monitor);
        SetWindowSize(config->windowWidth, config->windowHeight);
        ToggleFullscreen();

    }
}