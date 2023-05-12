#include <raylib.h>
#include "ghost.h"
#define ROUND(a) ((int)((a) + 0.5f))

Ghost::Ghost() {}

Ghost::Ghost(Vector2 coords) {
    centerPoint = coords;
    texture = LoadTexture("res/ghost.png");
}

Ghost::~Ghost() {}

void Ghost::update() {
    move();
    float dt = GetFrameTime();
    if (moveLeft) centerPoint.x -= 200 * dt;
    if (moveRight) centerPoint.x += 200 * dt;
    if (moveUp) centerPoint.y -= 200 * dt;
    if (moveDown) centerPoint.y += 200 * dt;
}

void Ghost::render() {
    DrawTexture(texture, ROUND(centerPoint.x - texture.width / 2), ROUND(centerPoint.y - texture.height / 2), WHITE);
}

void Ghost::move() {

    moveRight = false;
    moveLeft = false;
    moveUp = false;
    moveDown = false;

    actionLockCounter++;

    if (actionLockCounter >= 0 && actionLockCounter < 100) {
        moveRight = true;
    }
    else if (actionLockCounter >= 150 && actionLockCounter < 250) {
        moveDown = true;
    }
    else if (actionLockCounter >= 300 && actionLockCounter < 400) {
        moveLeft = true;
    }
    else if (actionLockCounter >= 450 && actionLockCounter < 550)
        moveUp = true;
    if (actionLockCounter == 600)
        actionLockCounter = 0;
}