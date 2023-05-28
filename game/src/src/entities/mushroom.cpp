#include <raylib.h>
#include "mushroom.hpp"
#include <cstdlib>
#include <iostream>
#define ROUND(a) ((int)((a) + 0.5f))

#include "../../main.hpp"
#include "../map/map.hpp"
Mushroom::Mushroom()
{
}

Mushroom::Mushroom(std::string idDebug, Config* config, Map* world) {
    this->idDebug = idDebug;
    this->map = config;
    this->world = world;
    this->isCaught = false;
    this->speed = 100.0;
    this->speedC = 100.0;
    this->centerPoint = { (500 + (rand() % (map->windowWidth - 500))) / 1.0F, (500 + (rand() % (map->windowHeight - 500))) / 1.0F };
    Image png = LoadImage("game/res/cute mushroom walk.png");
    textureWidth = TileWidth * 0.8;
    textureHeight = TileHeight * 0.8;
    ImageResizeNN(&png, textureWidth * 4, textureHeight * 4);
    this->texture = LoadTextureFromImage(png);
    UnloadImage(png);
}

Mushroom::~Mushroom()
{
}

void Mushroom::update() {
    if (!isCaught)
    {
        if (!world->canMove(centerPoint.x + 1, centerPoint.y + 1))
            centerPoint = { (500 + (rand() % (map->windowWidth - 500))) / 1.0F, (500 + (rand() % (map->windowHeight - 500))) / 1.0F };
        if ((moveUp == false && moveDown == false && moveRight == false && moveLeft == false) || randomRange <= 0.0
            || (centerPoint.x <= textureWidth / 2 || centerPoint.x >= map->windowWidth - textureWidth / 2 || centerPoint.y <= textureHeight / 2 || centerPoint.y >= map->windowHeight - textureHeight / 2))
            moveRandom();

        float dt = GetFrameTime();

        animTick += 1.0F;
        if (animTick >= 10.0F) {
            animIndex++;
            animTick = 0.0F;
        }
        if (animIndex == 4)
            animIndex = 0;

        randomRange -= dt;
        if (moveLeft)
        {
            dir = LEFT;
            if (centerPoint.x > textureWidth / 2 + 0.2)
            {
                if (world->canMove(((int)centerPoint.x - textureWidth / 2 + 0.2) - (this->speed * dt), (int)centerPoint.y)
                    && world->canMove(((int)centerPoint.x - textureWidth / 2 + 0.2) - (this->speed * dt), (int)centerPoint.y + textureHeight / 2 - 0.2)
                    && world->canMove(((int)centerPoint.x - textureWidth / 2 + 0.2) - (this->speed * dt), (int)centerPoint.y - textureHeight / 2 + 0.2))
                    centerPoint.x -= (this->speed * dt);
                else {
                    moveRandom();
                }
            }
            else
                centerPoint.x = textureWidth / 2 + 0.2;
        }

        if (moveRight)
        {
            dir = RIGHT;
            if (centerPoint.x < map->windowWidth - textureWidth / 2 - 0.2)
            {
                if (world->canMove(((int)centerPoint.x + textureWidth / 2 - 0.2) + (this->speed * dt), (int)centerPoint.y)
                    && world->canMove(((int)centerPoint.x + textureWidth / 2 - 0.2) + (this->speed * dt), (int)centerPoint.y + textureHeight / 2 - 0.2)
                    && world->canMove(((int)centerPoint.x + textureWidth / 2 - 0.2) + (this->speed * dt), (int)centerPoint.y - textureHeight / 2 + 0.2))
                    centerPoint.x += (this->speed * dt);
                else {
                    moveRandom();
                }
            }
            else
                centerPoint.x = map->windowWidth - textureWidth / 2 - 0.2;
        }

        if (moveUp)
        {
            dir = UP;
            if (centerPoint.y > textureHeight / 2 + 0.2)
            {
                if (world->canMove((int)centerPoint.x, (centerPoint.y - textureHeight / 2 + 0.2) - (this->speed * dt))
                    && world->canMove((int)centerPoint.x + textureWidth / 2 - 0.2, (centerPoint.y - textureHeight / 2 + 0.2) - (this->speed * dt))
                    && world->canMove((int)centerPoint.x - textureWidth / 2 + 0.2, (centerPoint.y - textureHeight / 2 + 0.2) - (this->speed * dt)))
                    centerPoint.y -= (this->speed * dt);
                else {
                    moveRandom();
                }
            }
            else
                centerPoint.y = textureHeight / 2 + 0.2; 
        }

        if (moveDown)
        {
            dir = DOWN;
            if (centerPoint.y < map->windowHeight - textureHeight / 2 - 0.2)
            {
                if (world->canMove((int)centerPoint.x, (centerPoint.y + textureHeight / 2 - 0.2) + (this->speed * dt))
                    && world->canMove((int)centerPoint.x + textureWidth / 2 - 0.2, (centerPoint.y + textureHeight / 2 - 0.2) + (this->speed * dt))
                    && world->canMove((int)centerPoint.x - textureWidth / 2 + 0.2, (centerPoint.y + textureHeight / 2 - 0.2) + (this->speed * dt)))
                    centerPoint.y += (this->speed * dt);
                else {
                    moveRandom();
                }
            }
            else
                centerPoint.y = map->windowHeight - textureHeight / 2 - 0.2;
        }
    }
    hitbox = { centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2, (float)textureWidth, (float)textureHeight };
    DebugXY = { centerPoint.x, centerPoint.y - textureHeight / 2 - 10 };
}

void Mushroom::render() {
    if (isCaught)
        DrawTexture(texture, centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2, LIGHTGRAY);
    else
        switch (dir)
        {
        case LEFT:
            DrawTextureRec(texture, Rectangle{ (float)textureWidth * animIndex, (float)textureHeight * 3,(float)textureWidth, (float)textureHeight },
                Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, LIGHTGRAY);
            break;
        case RIGHT:
            DrawTextureRec(texture, Rectangle{ (float)textureWidth * animIndex, (float)textureHeight * 1, (float)textureWidth, (float)textureHeight },
                Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, LIGHTGRAY);
            break;
        case UP:
            DrawTextureRec(texture, Rectangle{ (float)textureWidth * animIndex, (float)textureHeight*2, (float)textureWidth, (float)textureHeight },
                Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, LIGHTGRAY);
            break;
        case DOWN:
            DrawTextureRec(texture, Rectangle{ (float)textureWidth * animIndex, 0, (float)textureWidth, (float)textureHeight },
                Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, LIGHTGRAY);
            break;
        default:
            break;
        }
}

void Mushroom::moveRandom() {

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

Rectangle Mushroom::getHitbox()
{
    return hitbox;
}

void Mushroom::reloadTexture()
{
    UnloadTexture(texture);
    Image png = LoadImage("game/res/mushroom_dead.png");
    ImageResizeNN(&png, textureWidth, textureHeight);
    texture = LoadTextureFromImage(png);
    UnloadImage(png);
}

void Mushroom::reset()
{
    this->speed = this->speedC;
    this->centerPoint = generateRandomCoordinates();
    reloadTextureC();
    this->isCaught = false;
    moveRandom();
}

void Mushroom::reloadTextureC()
{
    UnloadTexture(texture);
    Image png = LoadImage("game/res/cute mushroom walk.png");
    ImageResizeNN(&png, textureWidth * 4, textureHeight * 4);
    texture = LoadTextureFromImage(png);
    UnloadImage(png);
}

Vector2 Mushroom::generateRandomCoordinates()
{
    Vector2 xy = { (500 + (rand() % (map->windowWidth - 500))) / 1.0F, (500 + (rand() % (map->windowHeight - 500))) / 1.0F };
    if (world->canMove(xy.x, xy.y))
        return xy;
    return generateRandomCoordinates();
}

void Mushroom::operator+(const int& n)
{
    this->idDebug = this->idDebug + std::to_string(n);
}