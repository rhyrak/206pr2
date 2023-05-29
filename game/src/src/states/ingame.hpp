#ifndef INGAME_H
#define INGAME_H
#define MAXSPOT 2

#include "../entities/player.hpp"
#include "../entities/strawberry.hpp"
#include "../entities/mushroom.hpp"
#include "cmath"
#include "state.hpp"
#include "../../main.hpp"
#include "raylib.h"
#include "../map/map.hpp"
#include "../util/GridLayout.hpp"
#include "../ui/IconButton.hpp"

/*InGame extends State*/
class InGame : public State
{
private:
    Player *player1;  /*Player Object*/
    Player *player2; 
    Camera2D camera;    /*Camera Object*/
    float visionRadius;
    bool nightVision;    /*cheat*/
    bool displayCoordinates;    /*cheat*/
    bool displayHitBoxes;   /*cheat*/
    Config* map;
    Map* world;
    GridLayout gl;
    Texture2D scoreboard;
    Texture2D gameoverBg;
    bool showScoreboard;
    bool isPaused;
    bool incrementOnce;
    std::vector<IconButton*> pauseBtns;
    std::vector<Strawberry*> strawberries;
    std::vector<Mushroom*> mushrooms;
public:
    InGame(Config *config); /*Constructor*/
    ~InGame();  /*Destructor*/
    void reset() override;
    inline void update() override; /*Overridden method*/
    inline void render() override; /*Overridden method*/
    Signal signal() override; /*Overridden method*/
    Player getPlayer(); /*Accessor*/
    Sound entityDeath;
    Sound player1Sound;
    Sound player2Sound;
    int monitor;
    unsigned int spotLoc[MAXSPOT];
    Vector2 spotPos[MAXSPOT];
    Vector2 spotVel[MAXSPOT];

    // use default vert shader
    Shader spotShader = LoadShader(0, "game/res/shaders/spotlight.fs");

};

#endif
