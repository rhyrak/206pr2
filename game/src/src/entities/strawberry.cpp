#include <raylib.h>
#include "strawberry.hpp"
#include <cstdlib>
#include <iostream>
#define ROUND(a) ((int)((a) + 0.5f))

#include "../../main.hpp"
#include "../map/map.hpp"
Strawberry::Strawberry()
{
}

Strawberry::Strawberry(std::string idDebug, Config *config, Map *world) {
    this->idDebug = idDebug;
    this->map = config;
    this->world = world;
    this->isCaught = false;
    this->speed = 100.0;
    this->speedC = 100.0;
    this->centerPoint = generateRandomCoordinates();
    Image png = LoadImage("game/res/Basic_Undead_strawberry_Sprites.png");
    textureHeight = TileHeight * 0.9;
    textureWidth = textureHeight * 29 / 38.0f;
    ImageResizeNN(&png, textureWidth * 9.0F, textureHeight * 4.0F);
    texture = LoadTextureFromImage(png);
    UnloadImage(png);
}

Strawberry::~Strawberry()
{
    UnloadTexture(texture);
}

void Strawberry::update() {
    if(!isCaught)
    {
        if(!world->canMove(centerPoint.x + 1, centerPoint.y + 1))
            centerPoint = { (500 + (rand() % (map->windowWidth - 500))) / 1.0F, (500 + (rand() % (map->windowHeight - 500))) / 1.0F };
        if ((moveUp == false && moveDown == false && moveRight == false && moveLeft == false) || randomRange <= 0.0
            || (centerPoint.x <= (double)textureWidth / 2 || centerPoint.x >= map->windowWidth - (double)textureWidth / 2
                || centerPoint.y <= (double)textureHeight / 2 || centerPoint.y >= map->windowHeight - (double)textureHeight / 2))
            moveRandom();

        float dt = GetFrameTime();

        animTick += 1.0F;
        if (animTick >= 10.0F) {
            animIndex++;
            animTick = 0.0F;
        }
        if (animIndex == 8)
            animIndex = 0;

        randomRange -= dt;
        if (moveLeft)
        {
            dir = LEFT;
            if (centerPoint.x > (double)textureWidth / 2 + 0.2)
            {
                if (world->canMove(((int)centerPoint.x - textureWidth / 2 + 0.2) - (this->speed * (double)dt), (int)centerPoint.y)
                    && world->canMove(((int)centerPoint.x - textureWidth / 2 + 0.2) - (this->speed * (double)dt), (int)centerPoint.y + textureHeight / 2 - 0.2)
                    && world->canMove(((int)centerPoint.x - textureWidth / 2 + 0.2) - (this->speed * (double)dt), (int)centerPoint.y - textureHeight / 2 + 0.2))
                    centerPoint.x -= (this->speed * (double)dt);
                else {
                    moveRandom();
                }
            }
            else
                centerPoint.x = (double)textureWidth / 2 + 0.2;
        }

        if (moveRight)
        {
            dir = RIGHT;
            if (centerPoint.x < map->windowWidth - (double)textureWidth / 2 - 0.2)
            {
                if (world->canMove(((int)centerPoint.x + (double)textureWidth / 2 - 0.2) + (this->speed * (double)dt), (int)centerPoint.y)
                    && world->canMove(((int)centerPoint.x + (double)textureWidth / 2 - 0.2) + (this->speed * (double)dt), (int)centerPoint.y + (double)textureHeight / 2 - 0.2)
                    && world->canMove(((int)centerPoint.x + (double)textureWidth / 2 - 0.2) + (this->speed * (double)dt), (int)centerPoint.y - (double)textureHeight / 2 + 0.2))
                    centerPoint.x += (this->speed * (double)dt);
                else {
                    moveRandom();
                }
            }
            else
                centerPoint.x = map->windowWidth - (double)textureWidth / 2 - 0.2;
        }

        if (moveUp)
        {
            dir = UP;
            if (centerPoint.y > (double)textureHeight / 2)
            {
                if (world->canMove((int)centerPoint.x, (centerPoint.y - (double)textureHeight / 2) - (this->speed * dt))
                    && world->canMove((int)centerPoint.x + (double)textureWidth / 2 - 0.2, (centerPoint.y - (double)textureHeight / 2) - (this->speed * (double)dt))
                    && world->canMove((int)centerPoint.x - (double)textureWidth / 2 + 0.2, (centerPoint.y - (double)textureHeight / 2) - (this->speed * (double)dt)))
                    centerPoint.y -= (this->speed * (double)dt);
                else {
                    moveRandom();
                }
            }
            else
                centerPoint.y = (double)textureHeight / 2;
        }

        if (moveDown)
        {
            dir = DOWN;
            if (centerPoint.y < map->windowHeight - (double)textureHeight / 2)
            {
                if (world->canMove((int)centerPoint.x, (centerPoint.y + (double)textureHeight / 2) + (this->speed * (double)dt))
                    && world->canMove((int)centerPoint.x + (double)textureWidth / 2 - 0.2, (centerPoint.y + (double)textureHeight / 2) + (this->speed * (double)dt))
                    && world->canMove((int)centerPoint.x - (double)textureWidth / 2 + 0.2, (centerPoint.y + (double)textureHeight / 2) + (this->speed * (double)dt)))
                    centerPoint.y += (this->speed * (double)dt);
                else {
                    moveRandom();
                }    
            }
            else
                centerPoint.y = map->windowHeight - (double)textureHeight / 2;
        }
    }
    hitbox = { centerPoint.x - (float)textureWidth / 2, centerPoint.y - (float)textureHeight / 2,(float) textureWidth,(float)textureHeight };
    DebugXY = {centerPoint.x, centerPoint.y - (float)textureHeight / 2 - 10};
}

void Strawberry::render() {
    if (isCaught)
        DrawTexture(texture, centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2, LIGHTGRAY);
    else
        switch (dir)
        {
        case LEFT:
            DrawTextureRec(texture, Rectangle{ (float)textureWidth * 9 - textureWidth * (animIndex + 1), textureHeight*1.0f, (float)textureWidth,(float)textureHeight },
                Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, LIGHTGRAY);
            break;
        case RIGHT:
            DrawTextureRec(texture, Rectangle{ (float)textureWidth * animIndex, textureHeight*0.0f, (float)textureWidth, (float)textureHeight},
                Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, LIGHTGRAY);
            break;
        case UP:
            DrawTextureRec(texture, Rectangle{ (float)textureWidth * animIndex, textureHeight*2.0f,(float)textureWidth,(float)textureHeight },
                Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, LIGHTGRAY);
            break;
        case DOWN:
            DrawTextureRec(texture, Rectangle{ (float)textureWidth * animIndex, textureHeight*3.0f, (float)textureWidth,(float)textureHeight},
                Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, LIGHTGRAY);
            break;
        default:
            break;
        }
}

void Strawberry::moveRandom() {
    
    moveRight = false;
    moveLeft = false;
    moveUp = false;
    moveDown = false;

    randomDir = 1 + (rand() % 8);
    randomRange = ((rand() % 3001) / 1000.0F) + 1.0;

    if (randomDir == 1) { 
        moveRight = true;
    }
    if (randomDir == 2) { 
        moveLeft = true;
    }
    if (randomDir == 3) { 
        moveUp = true;
        moveRight = true;
    }
    if (randomDir == 4) { 
        moveUp = true;
        moveLeft = true;
    }
    if (randomDir == 5) {
        moveUp = true;
    }
    if (randomDir == 6) {
        moveDown = true;
    }
    if (randomDir == 7) { 
        moveDown = true;
        moveRight = true;
    }
    if (randomDir == 8) {
        moveDown = true;
        moveLeft = true;
    }
}

Rectangle Strawberry::getHitbox()
{
    return hitbox;
}

void Strawberry::reloadTexture()
{
    UnloadTexture(texture);
    Image png = LoadImage("game/res/strawberry_dead.png");
    ImageResizeNN(&png, textureWidth, textureHeight);
    texture = LoadTextureFromImage(png);
    UnloadImage(png);
}

void Strawberry::reset()
{
    this->speed = this->speedC;
    this->centerPoint = generateRandomCoordinates();
    reloadTextureC();
    this->isCaught = false;
    moveRandom();
}

void Strawberry::reloadTextureC()
{
    UnloadTexture(texture);
    Image png = LoadImage("game/res/Basic_Undead_strawberry_Sprites.png");
    ImageResizeNN(&png, textureWidth * 9.0F, textureHeight * 4.0F);
    texture = LoadTextureFromImage(png);
    UnloadImage(png);
}

Vector2 Strawberry::generateRandomCoordinates()
{
    Vector2 xy = { (101 + (rand() % (map->windowWidth - 101))) / 1.0F, (101 + (rand() % (map->windowHeight - 101))) / 1.0F };
    if (world->canMove(xy.x, xy.y) && world->canMove(xy.x + textureWidth / 2, xy.y) && world->canMove(xy.x - textureWidth / 2, xy.y)
        && world->canMove(xy.x, xy.y + textureHeight / 2) && world->canMove(xy.x, xy.y - textureHeight / 2))
        return xy;
    return generateRandomCoordinates();
}

void Strawberry::operator+(const int& n)
{
    this->idDebug = this->idDebug + std::to_string(n);
}
