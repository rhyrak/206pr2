#ifndef MAIN_H
#define MAIN_H

#include <raylib.h>

typedef enum {
    S_NO_CHANGE     = -1,
    S_NAV_INGAME    = 1,
    S_NAV_MENU      = 2,
    S_NAV_SETTINGS  = 3,
    S_WIN_TOGGLE_FS = 4,
    S_WIN_CLOSE     = 5,
} Signal;

typedef struct {
    KeyboardKey p1Up, p1Down, p1Left, p1Right;
    KeyboardKey p2Up, p2Down, p2Left, p2Right;
} Keymap;

typedef struct {
    Keymap keymap;
    int windowWidth;
    int windowHeight;
    int cursorType;
    bool isFullscreen;
    bool isUpdated;
} Config;


extern	int player1score;
extern	int player2score;
extern  int TileWidth;
extern  int TileHeight;
extern  float ScaleFactor;
extern  float remTime;
extern  Font font;

#endif
