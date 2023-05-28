#include <raylib.h>
#include "player.hpp"
#include <cmath>

#define ROUND(a) ((int)((a) + 0.5f))
#include <string>
#include "../map/map.hpp"
#include "../../main.hpp"
#include <iostream>


Player::Player()
{
}

Player::Player(Config *map, std::string idDebug, Vector2 coords, KeyboardKey *upkey, KeyboardKey *downkey,
    KeyboardKey *leftKey, KeyboardKey *rightKey, Map* world)
{
    this->map = map;
    this->world = world;
    this->centerPoint = coords;
    this->speed = 200.0;
    //this->texture = this->getTexture("res/amogus.png", TileWidth, TileHeight);
    loadSprite();
    this->idDebug = idDebug + "'s coordinates:";
    /*Assign movement keys*/
    this->upKey = upkey;
    this->downKey = downkey;
    this->leftKey = leftKey;
    this->rightKey = rightKey;
}

void Player::loadSprite() {
    texture[0] = LoadTexture("res/_rightside walk.png");
    texture[1] = LoadTexture("res/_leftside walk.png");
    texture[2] = LoadTexture("res/_up walk.png");
    texture[3] = LoadTexture("res/_down walk.png");
    texture[4] = LoadTexture("res/_rightside idle.png");
    texture[5] = LoadTexture("res/_leftside idle.png");
    texture[6] = LoadTexture("res/_up idle.png");
    texture[7] = LoadTexture("res/_down idle.png");
}

Player::~Player()
{
}

void Player::render()
{
    if (idle && animIndex >= 5)
        animIndex = 0;
    if (!idle && animIndex >= 6)
        animIndex = 0;

    switch (dir)
    {
    case LEFT:
        if(!idle)
            if (animIndex < 4)
                DrawTextureRec(texture[1], Rectangle{(float)textureWidth *animIndex, 0,(float)textureWidth,(float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[1], Rectangle{ (float)textureWidth * (animIndex-4), 128, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        else
            if(animIndex < 4)
                DrawTextureRec(texture[5], Rectangle{ (float)textureWidth * animIndex, 0, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth/2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[5], Rectangle{ (float)textureWidth * (animIndex - 4), 128, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        break;
    case RIGHT:
        if (!idle)
            if (animIndex < 4)
                DrawTextureRec(texture[0], Rectangle{ (float)512 - textureWidth * (animIndex + 1), 0,(float)textureWidth,(float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[0], Rectangle{ (float)512 - textureWidth * (animIndex - 3), 128, (float)textureWidth,(float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        else
            if (animIndex < 4)
                DrawTextureRec(texture[4], Rectangle{ (float)512 - textureWidth * (animIndex + 1), 0,(float)textureWidth,(float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[4], Rectangle{ (float)512 - textureWidth * (animIndex - 3), 128, (float)textureWidth,(float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        break;
    case UP:
        if (!idle)
            if (animIndex < 4)
                DrawTextureRec(texture[2], Rectangle{ (float)textureWidth * animIndex, 0, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[2], Rectangle{ (float)textureWidth * (animIndex - 4), 128, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        else
            if (animIndex < 4)
                DrawTextureRec(texture[6], Rectangle{ (float)textureWidth * animIndex, 0, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[6], Rectangle{ (float)textureWidth * (animIndex - 4), 128, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        break;
    case DOWN:
        if (!idle)
            if (animIndex < 4)
                DrawTextureRec(texture[3], Rectangle{ (float)textureWidth * animIndex, 0, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[3], Rectangle{ (float)textureWidth * (animIndex - 4), 128, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        else
            if (animIndex < 4)
                DrawTextureRec(texture[7], Rectangle{ (float)textureWidth * animIndex, 0, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[7], Rectangle{ (float)textureWidth * (animIndex - 4), 128, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        break;
    default:
        break;
    }
}

/*Update coordinates according to key inputs*/
void Player::update()
{
    float dt = GetFrameTime();
    if (speed < 200.0F)
    {
        tick += dt;
        if (tick >= 1.5F)
        {
            changeSpeed(15.0F);
            tick = 0.0F;
            if (speed > 200.0F)
                speed = 200.0F;
        }
    }
    if (speed > 200.0F)
    {
        tick += dt;
        if (tick >= 1.5F)
        {
            changeSpeed(-10.0F);
            tick = 0.0F;
            if (speed < 200.0F)
                speed = 200.0F;
        }
    }
    std::cout << speed;
    animTick += 1.0;
    if (animTick >= 10.0F) {
        animIndex++;
        animTick = 0.0F;
    }
    if (!IsKeyDown(*leftKey) && !IsKeyDown(*rightKey) && !IsKeyDown(*upKey) && !IsKeyDown(*downKey))
        idle = true;
    else
        idle = false;

    if (IsKeyDown(*leftKey))
    {
        dir = LEFT;
        if(centerPoint.x > textureWidth / 4)
        {
            if (world->canMove(((int)centerPoint.x - textureWidth / 4) - (this->speed * dt), (int)centerPoint.y)
                && world->canMove(((int)centerPoint.x - textureWidth / 4) - (this->speed * dt), (int)centerPoint.y + textureHeight / 4 - 0.2)
                && world->canMove(((int)centerPoint.x - textureWidth / 4) - (this->speed * dt), (int)centerPoint.y - textureHeight / 4 + 0.2))
                centerPoint.x -= (this->speed * dt);
        }
        else
            centerPoint.x = textureWidth / 4;
    }      

    if (IsKeyDown(*rightKey))
    {
        dir = RIGHT;
        if(centerPoint.x < map->windowWidth - textureWidth / 4)
        {
            if(world->canMove(((int)centerPoint.x + textureWidth / 4) + (this->speed * dt), (int)centerPoint.y)
                && world->canMove(((int)centerPoint.x + textureWidth / 4) + (this->speed * dt), (int)centerPoint.y + textureHeight / 4 - 0.2)
                && world->canMove(((int)centerPoint.x + textureWidth / 4) + (this->speed * dt), (int)centerPoint.y - textureHeight / 4 + 0.2))
                centerPoint.x += (this->speed * dt);
        }
        else
            centerPoint.x = map->windowWidth - textureWidth / 4;
    }   

    if (IsKeyDown(*upKey))
    {
        dir = UP;
        if(centerPoint.y > textureHeight / 4)
        {
            if(world->canMove((int)centerPoint.x, (centerPoint.y - textureHeight / 4) - (this->speed * dt))
                && world->canMove((int)centerPoint.x + textureWidth / 4 - 0.2, (centerPoint.y - textureHeight / 4) - (this->speed * dt))
                && world->canMove((int)centerPoint.x - textureWidth / 4 + 0.2, (centerPoint.y - textureHeight / 4) - (this->speed * dt)))
                centerPoint.y -= (this->speed * dt);
        }
        else
            centerPoint.y = textureHeight / 4;
    }      

    if (IsKeyDown(*downKey))
    {
        dir = DOWN;
        if(centerPoint.y < map->windowHeight - textureHeight / 4)
        {
            if (world->canMove((int)centerPoint.x, (centerPoint.y + textureHeight / 4) + (this->speed * dt))
                && world->canMove((int)centerPoint.x + textureWidth / 4 - 0.2, (centerPoint.y + textureHeight / 4) + (this->speed * dt))
                && world->canMove((int)centerPoint.x - textureWidth / 4 + 0.2, (centerPoint.y + textureHeight / 4) + (this->speed * dt)))
                centerPoint.y += (this->speed * dt);
        }
        else
            centerPoint.y = map->windowHeight - textureHeight / 4;
    }

    hitbox = { centerPoint.x - 28, centerPoint.y - textureHeight / 4, (float) 48, (float) 72 };
}

int Player::getUpKey()
{
    return *this->upKey;
}

int Player::getDownKey()
{
    return *this->downKey;
}

int Player::getLeftKey()
{
    return *this->leftKey;
}

int Player::getRightKey()
{
    return *this->rightKey;
}

Rectangle Player::getHitbox() 
{
    return hitbox;
}

void Player::changeSpeed(float num) {
    speed += num;
}


