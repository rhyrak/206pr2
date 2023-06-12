
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
    int textureWidth, textureHeight;
    int animIndex = 0;
    Texture2D texture[12];
    //Image missingTexture;
    KeyboardKey *upKey;
    KeyboardKey *downKey;
    KeyboardKey *leftKey;
    KeyboardKey *rightKey;
    bool idle = true;
    bool picking = false;
    float animTick = 0.0F;
    void loadSprite();
    Map* world;
    float tick = 0.0F;
public:
    Player();   /*Default Constructor, don't use it lol*/
    Player(Config* map, std::string idDebug, Vector2 coords, KeyboardKey *upkey, KeyboardKey *downkey, KeyboardKey *leftKey, KeyboardKey *rightKey, Map* world);   /*Constructor*/
    ~Player();  /*Destructor*/
    void update();
    void render();
    void reset() override;
    int getUpKey();     /*Accesor*/
    int getDownKey();   /*Accesor*/
    int getLeftKey();   /*Accesor*/
    int getRightKey();  /*Accesor*/
    Rectangle getHitbox();
    void changeSpeed(float num);
    bool getStatus();
    void resetAnimIndex();
    void changePicking();
    bool getPicking();
};

#endif
