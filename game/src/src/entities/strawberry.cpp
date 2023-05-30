#include <raylib.h>
#include "strawberry.hpp"
#include <cstdlib>
#include <iostream>

inline int ROUND(float x) { return (int)(x + 0.5F); }

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
            this->centerPoint = generateRandomCoordinates();
        if ((moveUp == false && moveDown == false && moveRight == false && moveLeft == false) || randomRange <= 0.0
            || (this->centerPoint.x <= (double)this->textureWidth / 2 || this->centerPoint.x >= map->windowWidth - (double)this->textureWidth / 2
                || this->centerPoint.y <= (double)this->textureHeight / 2 || this->centerPoint.y >= map->windowHeight - (double)this->textureHeight / 2))
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
            if (this->centerPoint.x > (double)this->textureWidth / 2 + 0.2)
            {
                if (world->canMove(((int)this->centerPoint.x - textureWidth / 2 + 0.2) - (this->speed * (double)dt), (int)this->centerPoint.y)
                    && world->canMove(((int)this->centerPoint.x - textureWidth / 2 + 0.2) - (this->speed * (double)dt), (int)this->centerPoint.y + textureHeight / 2 - 0.2)
                    && world->canMove(((int)this->centerPoint.x - textureWidth / 2 + 0.2) - (this->speed * (double)dt), (int)this->centerPoint.y - textureHeight / 2 + 0.2))
                    this->centerPoint.x -= (this->speed * (double)dt);
                else {
                    moveRandom();
                }
            }
            else
                this->centerPoint.x = (double)this->textureWidth / 2 + 0.2;
        }

        if (moveRight)
        {
            dir = RIGHT;
            if (this->centerPoint.x < map->windowWidth - (double)this->textureWidth / 2 - 0.2)
            {
                if (world->canMove(((int)this->centerPoint.x + (double)this->textureWidth / 2 - 0.2) + (this->speed * (double)dt), (int)this->centerPoint.y)
                    && world->canMove(((int)this->centerPoint.x + (double)this->textureWidth / 2 - 0.2) + (this->speed * (double)dt), (int)this->centerPoint.y + (double)this->textureHeight / 2 - 0.2)
                    && world->canMove(((int)this->centerPoint.x + (double)this->textureWidth / 2 - 0.2) + (this->speed * (double)dt), (int)this->centerPoint.y - (double)this->textureHeight / 2 + 0.2))
                    this->centerPoint.x += (this->speed * (double)dt);
                else {
                    moveRandom();
                }
            }
            else
                this->centerPoint.x = map->windowWidth - (double)this->textureWidth / 2 - 0.2;
        }

        if (moveUp)
        {
            dir = UP;
            if (this->centerPoint.y > (double)this->textureHeight / 2)
            {
                if (world->canMove((int)this->centerPoint.x, (this->centerPoint.y - (double)this->textureHeight / 2) - (this->speed * dt))
                    && world->canMove((int)this->centerPoint.x + (double)this->textureWidth / 2 - 0.2, (this->centerPoint.y - (double)this->textureHeight / 2) - (this->speed * (double)dt))
                    && world->canMove((int)this->centerPoint.x - (double)this->textureWidth / 2 + 0.2, (this->centerPoint.y - (double)this->textureHeight / 2) - (this->speed * (double)dt)))
                    this->centerPoint.y -= (this->speed * (double)dt);
                else {
                    moveRandom();
                }
            }
            else
                this->centerPoint.y = (double)this->textureHeight / 2;
        }

        if (moveDown)
        {
            dir = DOWN;
            if (this->centerPoint.y < map->windowHeight - (double)this->textureHeight / 2)
            {
                if (world->canMove((int)this->centerPoint.x, (this->centerPoint.y + (double)this->textureHeight / 2) + (this->speed * (double)dt))
                    && world->canMove((int)this->centerPoint.x + (double)this->textureWidth / 2 - 0.2, (this->centerPoint.y + (double)this->textureHeight / 2) + (this->speed * (double)dt))
                    && world->canMove((int)this->centerPoint.x - (double)this->textureWidth / 2 + 0.2, (this->centerPoint.y + (double)this->textureHeight / 2) + (this->speed * (double)dt)))
                    this->centerPoint.y += (this->speed * (double)dt);
                else {
                    moveRandom();
                }    
            }
            else
                this->centerPoint.y = map->windowHeight - (double)this->textureHeight / 2;
        }
    }
    hitbox = { this->centerPoint.x - (float)this->textureWidth / 2, this->centerPoint.y - (float)this->textureHeight / 2,(float)this->textureWidth,(float)this->textureHeight };
    DebugXY = { this->centerPoint.x, this->centerPoint.y - (float)this->textureHeight / 2 - 10};
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
