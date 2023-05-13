#include <raylib.h>
#include "ghost.h"
#include <cstdlib>
#define ROUND(a) ((int)((a) + 0.5f))

Ghost::Ghost()
{
}

Ghost::Ghost(Config *config) {
    this->map = config;
    centerPoint = { (30 + (rand() % map->windowWidth)) / 1.0F, (30 + (rand() % map->windowHeight)) / 1.0F };
    texture = LoadTexture("res/ghost.png");
}

Ghost::~Ghost() {}

void Ghost::update() {

    if ((moveUp == false && moveDown == false && moveRight == false && moveLeft == false) || randomRange <= 0.0
        || (centerPoint.x <= texture.width/2 || centerPoint.x >= map->windowWidth - texture.width/2 || centerPoint.y <= texture.height/2 || centerPoint.y >= map->windowHeight - texture.height/2))
        moveRandom();

    float dt = GetFrameTime();
    randomRange -= dt;
    if (moveLeft)
    {
        if (centerPoint.x > 0.01)
        {
            centerPoint.x -= (100 * dt);
        }
        else
            centerPoint.x = 0.01;
    }

    if (moveRight)
    {
        if (centerPoint.x < map->windowWidth - 0.11)
        {
            centerPoint.x += (100 * dt);
        }
        else
            centerPoint.x = map->windowWidth - 0.1;
    }

    if (moveUp)
    {
        if (centerPoint.y > 0.01)
        {
            centerPoint.y -= (100 * dt);
        }
        else
            centerPoint.y = 0.01;
    }

    if (moveDown)
    {
        if (centerPoint.y < map->windowHeight - 0.11)
        {
            centerPoint.y += (100 * dt);
        }
        else
            centerPoint.y = map->windowHeight - 0.1;
    }
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