#include <raylib.h>
#include "ingame.h"
#include <iostream>

InGame::InGame(Config *config) : State(config)
{
    player = Player();
    camera = Camera2D{
        Vector2{0,0},
        player.getCenterPoint(),
        0.0F, 1.0F
    };
    isCameraLocked = true;
}

void InGame::update()
{
    float dt = GetFrameTime();
    player.update();
    if (IsKeyPressed(KEY_V)) isCameraLocked = !isCameraLocked;

    if (isCameraLocked) {
        camera.target.x = player.getCenterPoint().x - config->windowWidth/2;
        camera.target.y = player.getCenterPoint().y - config->windowHeight/2;
        camera.offset.x = 0;
        camera.offset.y = 0;
    }
    else {
        if (IsKeyDown(KEY_UP)) camera.offset.y -= dt * -300;
        if (IsKeyDown(KEY_DOWN)) camera.offset.y += dt * -300;
        if (IsKeyDown(KEY_RIGHT)) camera.offset.x += dt * -300;
        if (IsKeyDown(KEY_LEFT)) camera.offset.x -= dt * -300;
    }
}

void InGame::render()
{
    BeginMode2D(camera);

    ClearBackground(MAGENTA);
    // move this to map::render ____________________________________________________
    DrawRectangle(-1000, -1000, 1280+2000, 720+2000, DARKBLUE);
    DrawRectangle(0, 600, 1280, 120, DARKGREEN);
    DrawRectangle(300, 300, 50, 300, DARKBROWN);
    DrawTriangle(Vector2{ 325,150 }, Vector2{ 225,450 }, Vector2{ 425,450 }, GREEN);
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    player.render();
    
    EndMode2D();
    
    if (isCameraLocked)
        DrawCircle(10, 10, 5, RED);
}

char InGame::signal()
{
    return signalF;
}
