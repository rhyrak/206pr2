#include <raylib.h>
#include "player.h"

#define ROUND(a) ((int)((a) + 0.5f))
#include <string>

Player::Player()
{
    centerPoint = Vector2{ 600,575 };
    texture = LoadTexture("res/amogus.png");
}

Player::~Player()
{
}

void Player::render()
{
    DrawTexture(texture, ROUND(centerPoint.x - texture.width/2), ROUND(centerPoint.y - texture.height/2), WHITE);
}

void Player::update()
{
    float dt = GetFrameTime();
    if (IsKeyDown(KEY_A)) centerPoint.x -= 400 * dt;
    if (IsKeyDown(KEY_D)) centerPoint.x += 400 * dt;
    if (IsKeyDown(KEY_W)) centerPoint.y -= 400 * dt;
    if (IsKeyDown(KEY_S)) centerPoint.y += 400 * dt;
}


Vector2 Player::getCenterPoint() {
    return Vector2{ centerPoint.x,centerPoint.y };
}