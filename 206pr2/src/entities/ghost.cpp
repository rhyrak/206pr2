#include <raylib.h>
#include "ghost.hpp"
#include <cstdlib>
#include <iostream>
#define ROUND(a) ((int)((a) + 0.5f))

#include "../../main.hpp"
#include "../map/map.hpp"
Ghost::Ghost()
{
}

Ghost::Ghost(std::string idDebug, Config *config, Map *world) {
    this->idDebug = idDebug;
    this->map = config;
    this->world = world;
    this->isCaught = false;
    this->speed = 100.0;
    this->speedC = 100.0;
    this->centerPoint = generateRandomCoordinates();
    Image png = LoadImage("res/Basic_Undead_strawberry_Sprites.png");
    textureHeight = TileHeight * 0.9;
    textureWidth = textureHeight * 29 / 38.0f;
    ImageResizeNN(&png, textureWidth * 9.0F, textureHeight * 4.0F);
    texture = LoadTextureFromImage(png);
    UnloadImage(png);
}

Ghost::~Ghost()
{
}

void Ghost::update() {
    if(!isCaught)
    {
        if(!world->canMove(centerPoint.x, centerPoint.y))
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
        if (animIndex == 8)
            animIndex = 0;

        randomRange -= dt;
        if (moveLeft)
        {
            dir = LEFT;
            if (centerPoint.x > textureHeight / 2)
            {
                if (world->canMove(((int)centerPoint.x - textureWidth / 2) - (this->speed * dt), (int)centerPoint.y)
                    && world->canMove(((int)centerPoint.x - textureWidth / 2) - (this->speed * dt), (int)centerPoint.y + textureHeight / 2 - 0.2)
                    && world->canMove(((int)centerPoint.x - textureWidth / 2) - (this->speed * dt), (int)centerPoint.y - textureHeight / 2 + 0.2))
                    centerPoint.x -= (this->speed * dt);
                else {
                    moveRandom();
                }
            }
            else
                centerPoint.x = textureHeight / 2.0F;
        }

        if (moveRight)
        {
            dir = RIGHT;
            if (centerPoint.x < map->windowWidth - textureHeight / 2)
            {
                if (world->canMove(((int)centerPoint.x + textureWidth / 2) + (this->speed * dt), (int)centerPoint.y)
                    && world->canMove(((int)centerPoint.x + textureWidth / 2) + (this->speed * dt), (int)centerPoint.y + textureHeight / 2 - 0.2)
                    && world->canMove(((int)centerPoint.x + textureWidth / 2) + (this->speed * dt), (int)centerPoint.y - textureHeight / 2 + 0.2))
                    centerPoint.x += (this->speed * dt);
                else {
                    moveRandom();
                }
            }
            else
                centerPoint.x = map->windowWidth - textureHeight / 2;
        }

        if (moveUp)
        {
            dir = UP;
            if (centerPoint.y > textureHeight / 2)
            {
                if (world->canMove((int)centerPoint.x, (centerPoint.y - textureHeight / 2) - (this->speed * dt))
                    && world->canMove((int)centerPoint.x + textureWidth / 2 - 0.2, (centerPoint.y - textureHeight / 2) - (this->speed * dt))
                    && world->canMove((int)centerPoint.x - textureWidth / 2 + 0.2, (centerPoint.y - textureHeight / 2) - (this->speed * dt)))
                    centerPoint.y -= (this->speed * dt);
                else {
                    moveRandom();
                }
            }
            else
                centerPoint.y = textureHeight / 2;
        }

        if (moveDown)
        {
            dir = DOWN;
            if (centerPoint.y < map->windowHeight - textureHeight / 2)
            {
                if (world->canMove((int)centerPoint.x, (centerPoint.y + textureHeight / 2) + (this->speed * dt))
                    && world->canMove((int)centerPoint.x + textureWidth / 2 - 0.2, (centerPoint.y + textureHeight / 2) + (this->speed * dt))
                    && world->canMove((int)centerPoint.x - textureWidth / 2 + 0.2, (centerPoint.y + textureHeight / 2) + (this->speed * dt)))
                    centerPoint.y += (this->speed * dt);
                else {
                    moveRandom();
                }    
            }
            else
                centerPoint.y = map->windowHeight - textureHeight / 2;
        }
    }
    hitbox = { centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2,(float) textureWidth,(float)textureHeight };
    DebugXY = {centerPoint.x, centerPoint.y - texture.height / 2 - 10};
}

void Ghost::render() {
    if (isCaught)
        DrawTexture(texture, centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2, WHITE);
    else
        switch (dir)
        {
        case LEFT:
            DrawTextureRec(texture, Rectangle{ (float)textureWidth * 9 - textureWidth * (animIndex + 1), textureHeight*1.0f, (float)textureWidth,(float)textureHeight },
                Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            break;
        case RIGHT:
            DrawTextureRec(texture, Rectangle{ (float)textureWidth * animIndex, textureHeight*0.0f, (float)textureWidth, (float)textureHeight},
                Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            break;
        case UP:
            DrawTextureRec(texture, Rectangle{ (float)textureWidth * animIndex, textureHeight*2.0f,(float)textureWidth,(float)textureHeight },
                Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            break;
        case DOWN:
            DrawTextureRec(texture, Rectangle{ (float)textureWidth * animIndex, textureHeight*3.0f, (float)textureWidth,(float)textureHeight},
                Vector2{ centerPoint.x - textureWidth / 2, centerPoint.y - textureHeight / 2 }, WHITE);
            break;
        default:
            break;
        }
}

void Ghost::moveRandom() {
    
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

Rectangle Ghost::getHitbox()
{
    return hitbox;
}

void Ghost::reloadTexture()
{
    UnloadTexture(texture);
    Image png = LoadImage("res/strawberry_dead.png");
    ImageResizeNN(&png, textureWidth, textureHeight);
    texture = LoadTextureFromImage(png);
    UnloadImage(png);
}

void Ghost::reset()
{
    this->speed = this->speedC;
    this->centerPoint = generateRandomCoordinates();
    reloadTextureC();
    this->isCaught = false;
    moveRandom();
}

void Ghost::reloadTextureC()
{
    UnloadTexture(texture);
    Image png = LoadImage("res/Basic_Undead_strawberry_Sprites.png");
    ImageResizeNN(&png, textureWidth * 9.0F, textureHeight * 4.0F);
    texture = LoadTextureFromImage(png);
    UnloadImage(png);
}

Vector2 Ghost::generateRandomCoordinates()
{
    Vector2 xy = { (500 + (rand() % (map->windowWidth - 500))) / 1.0F, (500 + (rand() % (map->windowHeight - 500))) / 1.0F };
    if (world->canMove(xy.x, xy.y))
        return xy;
    return generateRandomCoordinates();
}

void Ghost::operator+(const int& n)
{
    this->idDebug = this->idDebug + std::to_string(n);
}
