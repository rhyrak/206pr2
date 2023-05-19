
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
    Texture2D texture;
    Image missingTexture;
    float speed = 1.0;
    int upKey = KeyboardKey::KEY_NULL;
    int downKey = KeyboardKey::KEY_NULL;
    int leftKey = KeyboardKey::KEY_NULL;
    int rightKey = KeyboardKey::KEY_NULL;
    Map* world;
public:
    Player();   /*Default Constructor, don't use it lol*/
    Player(Config* map, std::string idDebug, Vector2 coords, int upkey, int downkey, int leftKey, int rightKey, Map* world);   /*Constructor*/
    ~Player();  /*Destructor*/
    void update();
    void render();
    int getUpKey();     /*Accesor*/
    int getDownKey();   /*Accesor*/
    int getLeftKey();   /*Accesor*/
    int getRightKey();  /*Accesor*/
    Rectangle getHitbox();
};

#endif
