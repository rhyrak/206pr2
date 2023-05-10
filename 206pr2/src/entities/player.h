
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "entity.h"

class Player : public Entity
{
private:
    Texture2D texture;
public:
    Player();
    ~Player();
    void update();
    void render();
};

#endif
