#include <raylib.h>
#include "src/states/state.h"
#include "src/states/ingame.h"
#include "src/states/menu.h"
#include "main.h"

#include <iostream>

inline void cToggleFullscreen(Config*); /*Inline function, toggles Fullscreen mode*/

/*main function*/
int main(void)
{
    Config* config = new Config{ 1280,720 };    /*Define new Config Object*/
    /*Create window*/
    InitWindow(config->windowWidth, config->windowHeight, "Demo game with raylib");

    SetWindowState(FLAG_VSYNC_HINT);    /*Limit FPS to monitor's Refresh rate*/
    /* SetTargetFPS(60); */
    /* SetExitKey(32); */ /*27 is ESC, 32 is SPACEBAR, refer to ASCII table*/

    State *currentState = new Menu(config); /*Menu by default*/

    /*Game loop*/
    while (!WindowShouldClose())
    {
        /*Fullscreen shortcut*/
        if (IsKeyPressed(KEY_F)) cToggleFullscreen(config);
        
        currentState->update();

        BeginDrawing();

        currentState->render();

        DrawFPS(config->windowWidth-90, 10);
        EndDrawing();

        /*Change game state accordingly*/
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
    /*free up explicit-heap dynamic variable*/
    delete currentState;

    CloseWindow();

    return 0;
}

/*Enter and Exit Fullscreen mode*/
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