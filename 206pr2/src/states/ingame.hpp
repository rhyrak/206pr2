#ifndef INGAME_H
#define INGAME_H

#include "../entities/player.hpp"
#include "../entities/ghost.hpp"
#include "../textures/grid.hpp"
#include "cmath"
#include "state.hpp"
#include "../../main.hpp"
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
    float visionRadius;
    bool nightVision;    /*cheat*/
    bool coordinates;    /*cheat*/
    Config* map;
public:
    InGame(Config *config); /*Constructor*/
    inline void update() override; /*Overridden method*/
    inline void render() override; /*Overridden method*/
    int signal() override; /*Overridden method*/
    Player getPlayer(); /*Accessor*/
};

#endif
