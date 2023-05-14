#ifndef INGAME_H
#define INGAME_H
#define MAXSPOT 2

#include "../entities/player.hpp"
#include "../entities/ghost.hpp"
#include "cmath"
#include "state.hpp"
#include "../../main.hpp"
#include "raylib.h"

/*InGame extends State*/
class InGame : public State
{
private:
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

    int monitor;
    unsigned int spotLoc[MAXSPOT];
    Vector2 spotPos[MAXSPOT];
    Vector2 spotVel[MAXSPOT];

    // use default vert shader
    Shader spotShader = LoadShader(0, "res/shaders/spotlight.fs");


};

#endif
