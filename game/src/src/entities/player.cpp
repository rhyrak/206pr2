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
    this->centerPointC = coords;
    this->speed = 200.0;
    this->speedC = 200.0;
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
    textureHeight = TileHeight * 1.95F;
    textureWidth = TileWidth * 1.95F;

    Image png = LoadImage("game/res/_rightside walk.png");
    ImageResizeNN(&png, textureWidth * 4.0f, textureHeight * 2.0f);
    texture[0] = LoadTextureFromImage(png);

    png = LoadImage("game/res/_leftside walk.png");
    ImageResizeNN(&png, textureWidth * 4.0f, textureHeight * 2.0f);
    texture[1] = LoadTextureFromImage(png);

    png = LoadImage("game/res/_up walk.png");
    ImageResizeNN(&png, textureWidth * 4.0f, textureHeight * 2.0f);
    texture[2] = LoadTextureFromImage(png);

    png = LoadImage("game/res/_down walk.png");
    ImageResizeNN(&png, textureWidth * 4.0f, textureHeight * 2.0f);
    texture[3] = LoadTextureFromImage(png);

    png = LoadImage("game/res/_rightside idle.png");
    ImageResizeNN(&png, textureWidth * 4.0f, textureHeight * 2.0f);
    texture[4] = LoadTextureFromImage(png);

    png = LoadImage("game/res/_leftside idle.png");
    ImageResizeNN(&png, textureWidth * 4.0f, textureHeight * 2.0f);
    texture[5] = LoadTextureFromImage(png);

    png = LoadImage("game/res/_up idle.png");
    ImageResizeNN(&png, textureWidth * 4.0f, textureHeight * 2.0f);
    texture[6] = LoadTextureFromImage(png);

    png = LoadImage("game/res/_down idle.png");
    ImageResizeNN(&png, textureWidth * 4.0f, textureHeight * 2.0f);
    texture[7] = LoadTextureFromImage(png);

    png = LoadImage("game/res/_pick up right.png");
    ImageResizeNN(&png, textureWidth * 4.0f, textureHeight * 2.0f);
    texture[8] = LoadTextureFromImage(png);

    png = LoadImage("game/res/_pick up left.png");
    ImageResizeNN(&png, textureWidth * 4.0f, textureHeight * 2.0f);
    texture[9] = LoadTextureFromImage(png);

    png = LoadImage("game/res/_pick up up.png");
    ImageResizeNN(&png, textureWidth * 4.0f, textureHeight * 2.0f);
    texture[10] = LoadTextureFromImage(png);

    png = LoadImage("game/res/_pick up down.png");
    ImageResizeNN(&png, textureWidth * 4.0f, textureHeight * 2.0f);
    texture[11] = LoadTextureFromImage(png);

    UnloadImage(png);
}

Player::~Player()
{
}

void Player::render()
{
    if (idle && animIndex >= 5)
        resetAnimIndex();
    if (!idle && animIndex >= 6)
        resetAnimIndex();

    switch (dir)
    {
    case LEFT:
        if(!idle && !picking)
            if (animIndex < 4)
                DrawTextureRec(texture[1], Rectangle{(float)textureWidth *animIndex, textureHeight * 0.0F,(float)textureWidth,(float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[1], Rectangle{ (float)textureWidth * (animIndex-4), textureHeight * 1.0F, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        else if(idle && !picking)
            if(animIndex < 4)
                DrawTextureRec(texture[5], Rectangle{ (float)textureWidth * animIndex, textureHeight * 0.0F, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth/2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[5], Rectangle{ (float)textureWidth * (animIndex - 4), textureHeight * 1.0F, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        else if (picking)
            if (animIndex < 4)
                DrawTextureRec(texture[9], Rectangle{ (float)textureWidth * animIndex, textureHeight * 0.0F, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[9], Rectangle{ (float)textureWidth * (animIndex - 4), textureHeight * 1.0F, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        break;
    case RIGHT:
        if (!idle && !picking)
            if (animIndex < 4)
                DrawTextureRec(texture[0], Rectangle{ (float)textureWidth * 4 - textureWidth * (animIndex + 1), textureHeight * 0.0F,(float)textureWidth,(float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[0], Rectangle{ (float)textureWidth * 4 - textureWidth * (animIndex - 3), textureHeight * 1.0F, (float)textureWidth,(float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        else if (idle && !picking)
            if (animIndex < 4)
                DrawTextureRec(texture[4], Rectangle{ (float)textureWidth * 4 - textureWidth * (animIndex + 1), textureHeight * 0.0F,(float)textureWidth,(float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[4], Rectangle{ (float)textureWidth * 4 - textureWidth * (animIndex - 3), textureHeight * 1.0F, (float)textureWidth,(float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        else if (picking)
            if (animIndex < 4)
                DrawTextureRec(texture[8], Rectangle{ (float)textureWidth * animIndex, textureHeight * 0.0F,(float)textureWidth,(float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[8], Rectangle{ (float)textureWidth * 0, textureHeight * 1.0F, (float)textureWidth,(float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        break;
    case UP:
        if (!idle && !picking)
            if (animIndex < 4)
                DrawTextureRec(texture[2], Rectangle{ (float)textureWidth * animIndex, textureHeight * 0.0F, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[2], Rectangle{ (float)textureWidth * (animIndex - 4), textureHeight * 1.0F, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        else if(idle && !picking)
            if (animIndex < 4)
                DrawTextureRec(texture[6], Rectangle{ (float)textureWidth * animIndex, textureHeight * 0.0F, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[6], Rectangle{ (float)textureWidth * (animIndex - 4), textureHeight * 1.0F, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        else if (picking) {
            if (animIndex < 4)
                DrawTextureRec(texture[10], Rectangle{ (float)textureWidth * animIndex, textureHeight * 0.0F, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[10], Rectangle{ (float)textureWidth * (animIndex - 4), textureHeight * 1.0F, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        }
        break;
    case DOWN:
        if (!idle && !picking)
            if (animIndex < 4)
                DrawTextureRec(texture[3], Rectangle{ (float)textureWidth * animIndex, textureHeight * 0.0F, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[3], Rectangle{ (float)textureWidth * (animIndex - 4), textureHeight * 1.0F, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        else if(idle && !picking)
            if (animIndex < 4)
                DrawTextureRec(texture[7], Rectangle{ (float)textureWidth * animIndex, textureHeight * 0.0F, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[7], Rectangle{ (float)textureWidth * (animIndex - 4), textureHeight * 1.0F, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
        else if (picking)
            if (animIndex < 4)
                DrawTextureRec(texture[11], Rectangle{ (float)textureWidth * animIndex, textureHeight * 0.0F, (float)textureWidth, (float)textureHeight },
                    Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            else
                DrawTextureRec(texture[11], Rectangle{ (float)textureWidth * (animIndex - 4), textureHeight * 1.0F, (float)textureWidth, (float)textureHeight },
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
    
    animTick += 1.0;
    if (animTick >= 10.0F) {
        animIndex++;
        animTick = 0.0F;
    }
    if (!IsKeyDown(*leftKey) && !IsKeyDown(*rightKey) && !IsKeyDown(*upKey) && !IsKeyDown(*downKey) && !picking)
        idle = true;
    else
        idle = false;
    if (picking && animIndex >= 5) {
        resetAnimIndex();
        changePicking();
    }
    if (IsKeyDown(*leftKey) && !picking)
    {
        dir = LEFT;
        if(centerPoint.x > textureWidth / 4)
        {
            if (world->canMove(((int)centerPoint.x - textureWidth / 8) - (this->speed * dt), (int)centerPoint.y)
                && world->canMove(((int)centerPoint.x - textureWidth / 8) - (this->speed * dt), (int)centerPoint.y + textureHeight / 4 - 0.2)
                && world->canMove(((int)centerPoint.x - textureWidth / 8) - (this->speed * dt), (int)centerPoint.y - textureHeight / 4 + 0.2))
                centerPoint.x -= (this->speed * dt);
        }
        else
            centerPoint.x = textureWidth / 4;
    }      

    if (IsKeyDown(*rightKey) && !picking)
    {
        dir = RIGHT;
        if(centerPoint.x < map->windowWidth - textureWidth / 4)
        {
            if(world->canMove(((int)centerPoint.x + textureWidth / 8) + (this->speed * dt), (int)centerPoint.y)
                && world->canMove(((int)centerPoint.x + textureWidth / 8) + (this->speed * dt), (int)centerPoint.y + textureHeight / 4 - 0.2)
                && world->canMove(((int)centerPoint.x + textureWidth / 8) + (this->speed * dt), (int)centerPoint.y - textureHeight / 4 + 0.2))
                centerPoint.x += (this->speed * dt);
        }
        else
            centerPoint.x = map->windowWidth - textureWidth / 4;
    }   

    if (IsKeyDown(*upKey) && !picking)
    {
        dir = UP;
        if(centerPoint.y > textureHeight / 4)
        {
            if(world->canMove((int)centerPoint.x, (centerPoint.y - textureHeight / 4) - (this->speed * dt))
                && world->canMove((int)centerPoint.x + textureWidth / 8 - 0.2, (centerPoint.y - textureHeight / 4) - (this->speed * dt))
                && world->canMove((int)centerPoint.x - textureWidth / 8 + 0.2, (centerPoint.y - textureHeight / 4) - (this->speed * dt)))
                centerPoint.y -= (this->speed * dt);
        }
        else
            centerPoint.y = textureHeight / 4;
    }      

    if (IsKeyDown(*downKey) && !picking)
    {
        dir = DOWN;
        if(centerPoint.y < map->windowHeight - textureHeight / 4)
        {
            if (world->canMove((int)centerPoint.x, (centerPoint.y + textureHeight / 8) + (this->speed * dt))
                && world->canMove((int)centerPoint.x + textureWidth / 8 - 0.2, (centerPoint.y + textureHeight / 4) + (this->speed * dt))
                && world->canMove((int)centerPoint.x - textureWidth / 8 + 0.2, (centerPoint.y + textureHeight / 4) + (this->speed * dt)))
                centerPoint.y += (this->speed * dt);
        }
        else
            centerPoint.y = map->windowHeight - textureHeight / 4;
    }

    hitbox = { centerPoint.x - textureWidth/8, centerPoint.y - textureHeight / 4, (float)textureWidth / 4, (float)textureHeight / 2 };
}

void Player::reset()
{
    this->speed = this->speedC;
    this->centerPoint = this->centerPointC;
    this->dir = DOWN;
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

bool Player::getStatus()
{
    return idle;
}

void Player::resetAnimIndex() {
    animIndex = 0;
}

void Player::changePicking() {
    if (!picking)
        picking = true;  
    else
        picking = false;
}
