
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "entity.hpp"
#include "../../main.hpp"
#include "../map/map.hpp"

/*Player extends Entity*/
class Player : public Entity
{
private:
    enum direction {LEFT, RIGHT, UP, DOWN};
    direction dir = DOWN;
    int textureWidth = 128, textureHeight = 128;
    Texture2D texture[8];
    Image missingTexture;
    KeyboardKey *upKey;
    KeyboardKey *downKey;
    KeyboardKey *leftKey;
    KeyboardKey *rightKey;
    bool idle = true;
    float animTick = 0.0F;
    int animIndex = 0;
    void loadSprite();
    Map* world;
    float tick = 0.0F;
public:
    Player();   /*Default Constructor, don't use it lol*/
    Player(Config* map, std::string idDebug, Vector2 coords, KeyboardKey *upkey, KeyboardKey *downkey, KeyboardKey *leftKey, KeyboardKey *rightKey, Map* world);   /*Constructor*/
    ~Player();  /*Destructor*/
    void update();
    void render();
    int getUpKey();     /*Accesor*/
    int getDownKey();   /*Accesor*/
    int getLeftKey();   /*Accesor*/
    int getRightKey();  /*Accesor*/
    Rectangle getHitbox();
    void changeSpeed(float num);
};

#endif
