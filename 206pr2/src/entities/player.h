
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "entity.h"

/*Player extends Entity*/
class Player : public Entity
{
private:
    Texture2D texture;
    int upKey = KeyboardKey::KEY_NULL;
    int downKey = KeyboardKey::KEY_NULL;
    int leftKey = KeyboardKey::KEY_NULL;
    int rightKey = KeyboardKey::KEY_NULL;
public:
    Player();   /*Default Constructor, don't use it lol*/
    Player(std::string idDebug, int upkey, int downkey, int leftKey, int rightKey);   /*Constructor*/
    ~Player();  /*Destructor*/
    void update();
    void render();
    int getUpKey();     /*Accesor*/
    int getDownKey();   /*Accesor*/
    int getLeftKey();   /*Accesor*/
    int getRightKey();  /*Accesor*/
};

#endif
