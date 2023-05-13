#ifndef INGAME_H
#define INGAME_H

#include "../entities/player.h"
#include "../entities/ghost.h"
#include "../textures/grid.hpp"
#include "cmath"
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
    bool nightVision;    /*cheat*/
    Config* map;
public:
    InGame(Config *config); /*Constructor*/
    inline void update() override; /*Overridden method*/
    inline void render() override; /*Overridden method*/
    char signal() override; /*Overridden method*/
    Player getPlayer(); /*Accessor*/
};

#endif
