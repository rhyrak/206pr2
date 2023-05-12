#include <raylib.h>
#include "ghost.h"
#include <cstdlib>
#define ROUND(a) ((int)((a) + 0.5f))

Ghost::Ghost() {
    centerPoint = { (30 + (rand() % 2500)) / 1.0F, (30 + (rand() % 1411)) / 1.0F };
    texture = LoadTexture("res/ghost.png");
}

Ghost::~Ghost() {}

void Ghost::update() {

    if ((moveUp == false && moveDown == false && moveRight == false && moveLeft == false) || randomRange <= 0.0
        || (centerPoint.x <= 30.0 || centerPoint.x >= 2529.0 || centerPoint.y <= 30.0 || centerPoint.y >= 1441.0))
        moveRandom();

    float dt = GetFrameTime();
    randomRange -= dt;
    if (moveLeft) centerPoint.x -= 100 * dt;
    if (moveRight) centerPoint.x += 100 * dt;
    if (moveUp) centerPoint.y -= 100 * dt;
    if (moveDown) centerPoint.y += 100 * dt;
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