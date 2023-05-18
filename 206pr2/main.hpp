#ifndef MAIN_H
#define MAIN_H

#define S_NAV_INGAME 1
#define S_NAV_MENU 2
#define S_NAV_SETTINGS 3
#define S_WIN_TOGGLE_FS 4
#define S_WIN_CLOSE 5

typedef struct {
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

#endif
