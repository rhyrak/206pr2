#ifndef INGAME_H
#define INGAME_H

#include "../entities/player.h"
#include "../entities/ghost.h"
#include "../textures/grid.hpp"
#include "state.h"
#include "../../main.h"
#include "raylib.h"

/*InGame extends State*/
class InGame : public State
{
private:
    Grid grid;
    Player player1;  /*Player Object*/
    Player player2; 
    Ghost ghost;
    Camera2D camera;    /*Camera Object*/
    bool isCameraLocked;    /*Free-Cam flag*/
    Config* map;
public:
    InGame(Config *config); /*Constructor*/
    void update() override; /*Overridden method*/
    void render() override; /*Overridden method*/
    char signal() override; /*Overridden method*/
    Player getPlayer(); /*Accessor*/
};

#endif
