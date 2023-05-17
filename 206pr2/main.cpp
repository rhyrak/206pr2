#include <raylib.h>
#include "src/states/state.hpp"
#include "src/states/ingame.hpp"
#include "src/states/menu.hpp"
#include "src/states/settings.hpp"
#include "main.hpp"

#include <iostream>
#include "src/ui/UiElements.hpp"

int player1score;
int player2score;

inline void cToggleFullscreen(Config*); /*Inline function, toggles Fullscreen mode*/

/*main function*/
int main(void){
 
    Config* config = new Config{ 1896,1056,1,false,false };    /*Define new Config Object*/
    /*Create window*/
    InitWindow(config->windowWidth, config->windowHeight, "Demo game with raylib");

    SetWindowState(FLAG_VSYNC_HINT);    /*Limit FPS to monitor's Refresh rate*/
    /* SetTargetFPS(60); */
    /* SetExitKey(32); */ /*27 is ESC, 32 is SPACEBAR, refer to ASCII table*/

    HideCursor();
    Texture2D cursorActive = getTexture(CURSOR_ACTIVE, 2);
    Texture2D cursorHover = getTexture(CURSOR_HOVER, 2);

    State *currentState = new Menu(config); /*Menu by default*/

    /*Game loop*/
    bool exitFlag = false;
    while (!exitFlag && !WindowShouldClose())
    {
        /*Fullscreen shortcut*/
        if (IsKeyPressed(KEY_F)) cToggleFullscreen(config);
        
        currentState->update();
        //std::cout << player1score;
        BeginDrawing();

        currentState->render();

        DrawFPS(config->windowWidth-90, 10);

        switch (config->cursorType) {
        case 1: DrawTexture(cursorActive, GetMouseX(), GetMouseY(), WHITE); break;
        case 0: DrawTexture(cursorHover, GetMouseX(), GetMouseY(), WHITE); break;
        }

        EndDrawing();

        /*Change game state accordingly*/
        int signal = currentState->signal();
        switch (signal) {
            case S_NAV_MENU:
                delete currentState;
                currentState = new Menu(config);
                break;
            case S_NAV_INGAME:
                delete currentState;
                currentState = new InGame(config);
                break;
            case S_NAV_SETTINGS:
                delete currentState;
                currentState = new Settings(config);
                break;
            case S_WIN_TOGGLE_FS:
                cToggleFullscreen(config);
                break;
            case S_WIN_CLOSE:
                exitFlag = true;
                break;
            default:
                break;
            }

        config->isUpdated = false;
    }

    /*free up explicit-heap dynamic variable*/
    delete currentState;

    UnloadTexture(cursorActive);
    UnloadTexture(cursorHover);
    CloseWindow();

    return 0;
}

/*Enter and Exit Fullscreen mode*/
inline void cToggleFullscreen(Config *config) 
{
    config->isFullscreen = !config->isFullscreen;
    config->isUpdated = true;
    if (IsWindowFullscreen())
    {
        config->windowHeight = 1056;
        config->windowWidth = 1896;
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