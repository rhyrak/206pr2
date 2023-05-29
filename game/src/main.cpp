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
    InitAudioDevice();
    Music music = LoadMusicStream("game/res/background.wav");
    PlayMusicStream(music);
    
    // create config object and load data from file
    Config* config = new Config;
    *config << "config.bin";

    SetMusicVolume(music, config->musicLevel);

    /*Create window*/
    InitWindow(config->windowWidth, config->windowHeight, "Demo game with raylib");
    if (config->windowHeight == 721)
    {
        int monitor = GetCurrentMonitor();
        config->windowWidth = GetMonitorWidth(monitor) * 0.75F;
        config->windowHeight = config->windowWidth * (9.0F / 16);
        SetWindowSize(config->windowWidth, config->windowHeight);
    }

    SetWindowState(FLAG_VSYNC_HINT);    /*Limit FPS to monitor's Refresh rate*/
    /* SetTargetFPS(60); */
    /* SetExitKey(32); */ /*27 is ESC, 32 is SPACEBAR, refer to ASCII table*/

    if (config->isFullscreen && !IsWindowFullscreen())
        ToggleFullscreen();

    if (!IsWindowFullscreen())
    {
        int monitor = GetCurrentMonitor();
        SetWindowPosition((GetMonitorWidth(monitor) - config->windowWidth) / 2,
            (GetMonitorHeight(monitor) - config->windowHeight) / 2);
    }

    HideCursor();
    Texture2D cursorActive = getTexture(CURSOR_ACTIVE, 3);
    Texture2D cursorHover = getTexture(CURSOR_HOVER, 3);
    font = LoadFontEx("game/res/ui/Kenney Mini Square Mono.ttf", 96, NULL, 0);

    std::vector<State*> stateStack;
    stateStack.push_back(new Menu(config));

    /*Game loop*/
    bool exitFlag = false;
    config->isUpdated = true; // force an update when the game is started
    while (!exitFlag && !WindowShouldClose())
    {
        UpdateMusicStream(music);
        SetMusicVolume(music, config->musicLevel);
        /*Fullscreen shortcut*/
        if (!instanceof<InGame>(stateStack.back())) {
            if (IsKeyPressed(KEY_F)) cToggleFullscreen(config);
        }

        if (IsKeyPressed(KEY_Q) && IsKeyDown(KEY_LEFT_ALT)) MinimizeWindow();
        
        stateStack.back()->update();
        //std::cout << player1score;
        BeginDrawing();

        stateStack.back()->render();

        DrawFPS(config->windowWidth-90, 10);

        switch (config->cursorType) {
        case 1: DrawTexture(cursorActive, GetMouseX(), GetMouseY(), WHITE); break;
        case 0: DrawTexture(cursorHover, GetMouseX(), GetMouseY(), WHITE); break;
        }

        EndDrawing();
        config->isUpdated = false;
        /*Change game state accordingly*/
        Signal signal = stateStack.back()->signal();
        switch (signal) {
            case S_NAV_MENU:
                for (auto state : stateStack)
                    delete state;
                stateStack.clear();
                stateStack.push_back(new Menu(config));
                break;
            case S_NAV_INGAME:
                if (!instanceof<InGame>(stateStack.back()))
                {
                    for (auto state : stateStack)
                        delete state;
                    stateStack.clear();
                    stateStack.push_back(new InGame(config));
                }
                else
                    stateStack.back()->reset();
                break;
            case S_NAV_SETTINGS:
                for (auto state : stateStack)
                    delete state;
                stateStack.clear();
                stateStack.push_back(new Settings(config));
                break;
            case S_NAV_PUSH_SETTINGS:
                stateStack.push_back(new Settings(config));
                break;
            case S_NAV_POP:
                delete stateStack.at(stateStack.size()-1);
                stateStack.pop_back();
                if (stateStack.size()==0)
                    stateStack.push_back(new Menu(config));
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
    }

    /*free up explicit-heap dynamic variables*/
    for (auto state : stateStack)
        delete state;
    stateStack.clear();
    UnloadMusicStream(music);
    CloseAudioDevice();

    UnloadTexture(cursorActive);
    UnloadTexture(cursorHover);
    UnloadFont(font);
    CloseWindow();

    // save config data to file
    *config >> "config.bin";

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
        config->windowWidth = GetMonitorWidth(monitor) * 0.75F;
        config->windowHeight = config->windowWidth * (9.0F / 16);
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

void Config::operator<<(const char* fileName) {
    FILE* configFile;
    errno_t res = fopen_s(&configFile, fileName, "rb");
    if (res == EINVAL || configFile == 0)
    {
        std::cout << "CREATING DEFAULT CONFIG\n";
        *this = Config{
            { KEY_W,KEY_S,KEY_A,KEY_D,KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT },
            0.95F,0.95F,1280,721,1,false,false };    /*Define new Config Object*/
    }
    else
    {
        std::cout << "READING SAVED CONFIG\n";
        fread(this, sizeof(Config), 1, configFile);
        fclose(configFile);
    }
}

void Config::operator>>(const char* fileName) {
    FILE* configFile;
    errno_t res = fopen_s(&configFile, fileName, "wb");
    if (res != EINVAL && configFile != 0)
    {
        fwrite(this, sizeof(Config), 1, configFile);
    }
}