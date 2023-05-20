#include <raylib.h>
#include <iostream>

#include "src/states/state.hpp"
#include "src/states/ingame.hpp"
#include "src/states/menu.hpp"
#include "src/states/settings.hpp"
#include "main.hpp"
#include "src/ui/UiElements.hpp"

int player1score;
int player2score;
float ScaleFactor = 0.6;
float remTime = 0;
Font font;

inline void cToggleFullscreen(Config*); /*Inline function, toggles Fullscreen mode*/

/*Java-like instanceof function (Thanks stackoverflow.com)*/
template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

/*main function*/
int main(void){
 
    Config* config;
    FILE* configFile;
    errno_t res = fopen_s(&configFile, "config.bin", "rb");
    if (res == EINVAL || configFile == 0)
    {
        std::cout << "CREATING DEFAULT CONFIG\n";
        config = new Config{
            { KEY_W,KEY_S,KEY_A,KEY_D,KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT },
            1600,900,1,false,false };    /*Define new Config Object*/
    }
    else
    {
        std::cout << "READING SAVED CONFIG\n";
        config = new Config;
        fread(config, sizeof(Config), 1, configFile);
        fclose(configFile);
    }


    /*Create window*/
    InitWindow(config->windowWidth, config->windowHeight, "Demo game with raylib");

    SetWindowState(FLAG_VSYNC_HINT);    /*Limit FPS to monitor's Refresh rate*/
    /* SetTargetFPS(60); */
    /* SetExitKey(32); */ /*27 is ESC, 32 is SPACEBAR, refer to ASCII table*/

    if (config->isFullscreen && !IsWindowFullscreen())
        ToggleFullscreen();

    HideCursor();
    Texture2D cursorActive = getTexture(CURSOR_ACTIVE, 3);
    Texture2D cursorHover = getTexture(CURSOR_HOVER, 3);
    font = LoadFontEx("res/ui/Kenney Mini Square Mono.ttf", 96, NULL, 0);

    State *currentState = new Menu(config); /*Menu by default*/

    /*Game loop*/
    bool exitFlag = false;
    config->isUpdated = true; // force an update when the game is started
    while (!exitFlag && !WindowShouldClose())
    {
        /*Fullscreen shortcut*/
        if (!instanceof<InGame>(currentState)) {
            if (IsKeyPressed(KEY_F)) cToggleFullscreen(config);
        }

        if (IsKeyPressed(KEY_Q) && IsKeyDown(KEY_LEFT_ALT)) MinimizeWindow();
        
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
        Signal signal = currentState->signal();
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
    UnloadFont(font);
    CloseWindow();

    res = fopen_s(&configFile, "config.bin", "wb");
    if (res != EINVAL && configFile != 0)
    {
        fwrite(config, sizeof(Config), 1, configFile);
    }

    return 0;
}

/*Enter and Exit Fullscreen mode*/
inline void cToggleFullscreen(Config *config) 
{
    config->isFullscreen = !config->isFullscreen;
    config->isUpdated = true;

    int monitor = GetCurrentMonitor();
    if (IsWindowFullscreen())
    {
        config->windowHeight = 900;
        config->windowWidth = 1600;
        ToggleFullscreen();
        SetWindowSize(config->windowWidth, config->windowHeight);
        SetWindowPosition((GetMonitorWidth(monitor) - config->windowWidth) / 2,
            (GetMonitorHeight(monitor) - config->windowHeight) / 2);
    }
    else
    {
        config->windowHeight = GetMonitorHeight(monitor);
        config->windowWidth = GetMonitorWidth(monitor);
        SetWindowSize(config->windowWidth, config->windowHeight);
        ToggleFullscreen();
    }
}