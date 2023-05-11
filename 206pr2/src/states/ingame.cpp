#include <raylib.h>
#include "ingame.h"
#include <iostream>

InGame::InGame(Config *config) : State(config)
{
    /*Create new Player*/
    player = Player(
        "Player 1",
        { (float)config->windowWidth, (float)config->windowHeight },
        KeyboardKey::KEY_W,
        KeyboardKey::KEY_S,
        KeyboardKey::KEY_A,
        KeyboardKey::KEY_D
    );

    /*Create Camera*/
    camera = Camera2D{
        Vector2{0,0},
        player.getCenterPoint(),
        0.0F, 1.0F
    };

    isCameraLocked = true;  /*enable flag by default*/
    map = new Config{ config->windowWidth*2, 1472 };
    grid = Grid(map);
}

void InGame::update()
{
    float dt = GetFrameTime();
    player.update();
    if (IsKeyPressed(KEY_V)) isCameraLocked = !isCameraLocked;  /*toggle flag*/

    /*update camera position according to flag*/
    if (isCameraLocked) 
    {
        camera.target.x = player.getCenterPoint().x - config->windowWidth/2;
        camera.target.y = player.getCenterPoint().y - config->windowHeight/2;
        camera.offset.x = 0;
        camera.offset.y = 0;
        
        player.xDebug.x = player.getCenterPoint().x - config->windowWidth / 2 + 30;
        player.xDebug.y = player.getCenterPoint().y - config->windowHeight / 2 + 35;
        player.yDebug.x = player.getCenterPoint().x - config->windowWidth / 2 + 30;
        player.yDebug.y = player.getCenterPoint().y - config->windowHeight / 2 + 35;    
    }

}

void InGame::render()
{
    BeginMode2D(camera);

    ClearBackground(MAGENTA);
    // move this to map::render ____________________________________________________
    DrawRectangle(0, 0, map->windowWidth, map->windowHeight, DARKBLUE);
    DrawRectangle(0, 600, 1280, 120, DARKGREEN);
    DrawRectangle(300, 300, 50, 300, DARKBROWN);
    DrawTriangle(Vector2{ 325,150 }, Vector2{ 225,450 }, Vector2{ 425,450 }, GREEN);
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    player.render();    /*Draw player model*/
    player.displayDebugInfo();  /*Display coordinates*/

    /*Shadow Experimental*/
    for (int i = 0; i < grid.config->windowWidth / grid.size; i++) {
        for (int j = 0; j < grid.config->windowHeight / grid.size; j++) {
            if (CheckCollisionCircleRec(player.getCenterPoint(), (float)16, grid.getRectangle({ (float)i, (float)j }))) {
                if ((player.getCenterPoint().x)/grid.size != i && (player.getCenterPoint().y)/grid.size != j) {
                    grid.render({ (float)i * grid.size, (float)j * grid.size });
                }
            }

        }
    }

    EndMode2D();
    
    if (isCameraLocked)
        DrawCircle(10, 10, 5, RED); /*Indicator for Free-cam mode*/
}

/*Accessor*/
char InGame::signal()
{
    return signalF;
}

/*Accessor*/
Player InGame::getPlayer()
{
    return player;
}
