#include <raylib.h>
#include "ingame.h"
#include <iostream>

InGame::InGame(Config *config) : State(config)
{
    map = new Config{ config->windowWidth * 2, 1472 };

    /*Create new Player*/
    player1 = Player(
        map,
        "Player 1",
        { 100.0, 100.0 },
        KeyboardKey::KEY_W,
        KeyboardKey::KEY_S,
        KeyboardKey::KEY_A,
        KeyboardKey::KEY_D
    );


    player2 = Player(
        map,
        "Player 2",
        { (float)(map->windowWidth - 100.0), (float)(map->windowHeight - 100.0) },
        KeyboardKey::KEY_UP,
        KeyboardKey::KEY_DOWN,
        KeyboardKey::KEY_LEFT,
        KeyboardKey::KEY_RIGHT
    );


    ghost = Ghost();
    /*Create Camera*/
    camera = Camera2D{
        Vector2{0,0},
        player1.getCenterPoint(),
        0.0F, 0.4F
    };

    isCameraLocked = true;  /*enable flag by default*/
    grid = Grid(map);
}

void InGame::update()
{
    float dt = GetFrameTime();
    player1.update();
    player2.update();
    if (IsKeyPressed(KEY_V)) isCameraLocked = !isCameraLocked;  /*toggle flag*/
    ghost.update();
    /*update camera position according to flag*/
    if (isCameraLocked) 
    {
        camera.target.x = player1.getCenterPoint().x - config->windowWidth/2;
        camera.target.y = player1.getCenterPoint().y - config->windowHeight/2;
        camera.offset.x = 0;
        camera.offset.y = 0;
        
        player1.xDebug.x = player1.getCenterPoint().x - config->windowWidth / 2 + 30;
        player1.xDebug.y = player1.getCenterPoint().y - config->windowHeight / 2 + 35;
        player1.yDebug.x = player1.getCenterPoint().x - config->windowWidth / 2 + 30;
        player1.yDebug.y = player1.getCenterPoint().y - config->windowHeight / 2 + 35;    
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
    player1.render();    /*Draw player model*/
    player2.render();
    ghost.render();
    /*Shadow Experimental*/
    for (int j = 0; j < grid.config->windowWidth / grid.size; j++) {
        for (int i = 0; i < grid.config->windowHeight / grid.size; i++) {
            if (!CheckCollisionCircleRec(player1.getCenterPoint(), 148, grid.getRectangle({(float)i, (float)j})) && !CheckCollisionCircleRec(player2.getCenterPoint(),148, grid.getRectangle({(float)i, (float)j}))) {
                    grid.render({ (float)j * grid.size, (float)i * grid.size });
            }
        }
    }

    player1.displayDebugInfo();  /*Display coordinates*/

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
    return player1;
}
