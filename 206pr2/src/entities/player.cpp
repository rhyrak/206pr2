#include <raylib.h>
#include "player.h"

#define ROUND(a) ((int)((a) + 0.5f))
#include <string>


Player::Player()
{
}

Player::Player(std::string idDebug, int upkey, int downkey, int leftKey, int rightKey)
{
    centerPoint = Vector2{ 600,575 };
    texture = LoadTexture("res/amogus.png");
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
    if (IsKeyDown(leftKey)) centerPoint.x -= 400 * dt;
    if (IsKeyDown(rightKey)) centerPoint.x += 400 * dt;
    if (IsKeyDown(upKey)) centerPoint.y -= 400 * dt;
    if (IsKeyDown(downKey)) centerPoint.y += 400 * dt;
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
