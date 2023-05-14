#include <raylib.h>
#include "ingame.hpp"
#include <iostream>

InGame::InGame(Config *config) : State(config)
{
    map = new Config{ config->windowWidth * 2, config->windowHeight * 2};

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


    ghost = Ghost(map);
    /*Create Camera*/
    camera = Camera2D{
        Vector2{(float) config->windowWidth / 2 + 12, (float) config->windowHeight / 2 + 12},
        {(float)map->windowWidth / 2, (float)map->windowHeight / 2 },
        0.0F, 0.5F
    };

    nightVision = false;  /*disable flag by default*/
    coordinates = false;  /*disable flag by default*/
    visionRadius = 148.0;
    grid = Grid(map);
}

inline void InGame::update()
{
    float dt = GetFrameTime();
    player1.update();
    player2.update();
    ghost.update();
    if (IsKeyPressed(KEY_N)) nightVision = !nightVision; /*toggle flag*/
    if (IsKeyPressed(KEY_C)) coordinates = !coordinates; /*toggle flag*/
}

inline void InGame::render()
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
    if (!nightVision)
    {
        for (int j = 0; j < grid.config->windowWidth / grid.size; j++) {
            for (int i = 0; i < grid.config->windowHeight / grid.size; i++) {
                if (!CheckCollisionCircleRec(player1.getCenterPoint(), visionRadius, grid.getShadow({ (float)i, (float)j }).shape)
                    && !CheckCollisionCircleRec(player2.getCenterPoint(), visionRadius, grid.getShadow({ (float)i, (float)j }).shape))
                {
                    grid.render({ (float)i, (float)j });
                }
            }
        }
    }

    if (coordinates)
    {
        DrawCircleLines(player1.getCenterPoint().x, player1.getCenterPoint().y, 148, RED);
        DrawCircleLines(player2.getCenterPoint().x, player2.getCenterPoint().y, 148, RED);
    }

    EndMode2D();

    if(coordinates)
    {
        player1.displayDebugInfo(20);  /*Display coordinates*/
        player2.displayDebugInfo(80);  /*Display coordinates*/
    } 
}

/*Accessor*/
int InGame::signal()
{
    return signalF;
}

/*Accessor*/
Player InGame::getPlayer()
{
    return player1;
}
