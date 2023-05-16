#include <raylib.h>
#include "ghost.hpp"
#include <cstdlib>
#define ROUND(a) ((int)((a) + 0.5f))

Ghost::Ghost()
{
}

Ghost::Ghost(std::string idDebug, Config *config) {
    this->idDebug = idDebug;
    this->map = config;
    this->isCaught = false;
    this->centerPoint = { (30 + (rand() % map->windowWidth)) / 1.0F, (30 + (rand() % map->windowHeight)) / 1.0F };
    this->texture = getTexture("res/ghost.png");
}

Ghost::~Ghost()
{
}

void Ghost::update() {

    if(!isCaught)
    {
        if ((moveUp == false && moveDown == false && moveRight == false && moveLeft == false) || randomRange <= 0.0
            || (centerPoint.x <= texture.width / 2 || centerPoint.x >= map->windowWidth - texture.width / 2 || centerPoint.y <= texture.height / 2 || centerPoint.y >= map->windowHeight - texture.height / 2))
            moveRandom();

        float dt = GetFrameTime();
        randomRange -= dt;
        if (moveLeft)
        {
            if (centerPoint.x > texture.height / 2)
            {
                centerPoint.x -= (100 * dt);
            }
            else
                centerPoint.x = texture.height / 2;
        }

        if (moveRight)
        {
            if (centerPoint.x < map->windowWidth - texture.height / 2)
            {
                centerPoint.x += (100 * dt);
            }
            else
                centerPoint.x = map->windowWidth - texture.height / 2;
        }

        if (moveUp)
        {
            if (centerPoint.y > texture.height / 2)
            {
                centerPoint.y -= (100 * dt);
            }
            else
                centerPoint.y = texture.height / 2;
        }

        if (moveDown)
        {
            if (centerPoint.y < map->windowHeight - texture.height / 2)
            {
                centerPoint.y += (100 * dt);
            }
            else
                centerPoint.y = map->windowHeight - texture.height / 2;
        }
    }
    hitbox = { centerPoint.x - texture.width / 2, centerPoint.y - texture.height / 2, (float)texture.width, (float)texture.height };
    DebugXY = {centerPoint.x, centerPoint.y-texture.height/2-10};
}

void Ghost::render() {
    DrawTexture(texture, ROUND(centerPoint.x - texture.width / 2), ROUND(centerPoint.y - texture.height / 2), WHITE);
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
    texture = getTexture("res/dead_ghost.png");
}

Texture2D Ghost::getTexture(const char* path)
{
    try {
        texture = LoadTexture(path);
        if (texture.id <= 0) throw 0;
    }
    catch (...) {
        missingTexture = GenImageChecked(64, 64, 32, 32, PURPLE, BLACK);
        texture = LoadTextureFromImage(missingTexture);
        UnloadImage(missingTexture);
        return texture;
    }
}