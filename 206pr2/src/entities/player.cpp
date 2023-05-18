#include <raylib.h>
#include "player.hpp"
#include <cmath>

#define ROUND(a) ((int)((a) + 0.5f))
#include <string>
#include "../map/map.hpp"


Player::Player()
{
}

Player::Player(Config *map, std::string idDebug, Vector2 coords, int upkey, int downkey, int leftKey, int rightKey, Map* world)
{
    this->map = map;
    this->world = world;
    this->centerPoint = coords;
    this->missingTexture = GenImageChecked(400, 400, 1, 1, PURPLE, BLACK);
    this->texture = this->getTexture("res/amogus.png");
    this->idDebug = idDebug + "'s coordinates:";
    /*Assign movement keys*/
    this->upKey = upkey;
    this->downKey = downkey;
    this->leftKey = leftKey;
    this->rightKey = rightKey;
}

Player::~Player()
{
}

void Player::render()
{
    DrawTexture(texture, ROUND(centerPoint.x - texture.width/2), ROUND(centerPoint.y - texture.height/2), WHITE);
}

/*Update coordinates according to key inputs*/
void Player::update()
{
    float dt = GetFrameTime();
    if (IsKeyDown(leftKey))
    {
        if(centerPoint.x > texture.width / 2)
        {
            centerPoint.x -= (400 * dt);
        }
        else
            centerPoint.x = texture.width / 2;
    }      

    if (IsKeyDown(rightKey))
    {
        if(centerPoint.x < map->windowWidth - texture.width / 2)
        {
            centerPoint.x += (400 * dt);
        }
        else
            centerPoint.x = map->windowWidth - texture.width / 2;
    }   

    if (IsKeyDown(upKey))
    {
        if(centerPoint.y > texture.height / 2)
        {
            centerPoint.y -= (400 * dt);
        }
        else
            centerPoint.y = texture.height / 2;
    }      

    if (IsKeyDown(downKey))
    {
        if(centerPoint.y < map->windowHeight - texture.height / 2)
        {
            centerPoint.y += (400 * dt);
        }
        else
            centerPoint.y = map->windowHeight - texture.height / 2;
    }

    hitbox = { centerPoint.x - texture.width / 2, centerPoint.y - texture.height / 2, (float)texture.width, (float)texture.height };
          
}

int Player::getUpKey()
{
    return this->upKey;
}

int Player::getDownKey()
{
    return this->downKey;
}

int Player::getLeftKey()
{
    return this->leftKey;
}

int Player::getRightKey()
{
    return this->rightKey;
}

Rectangle Player::getHitbox() 
{
    return hitbox;
}

