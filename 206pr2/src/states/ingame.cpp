#include <raylib.h>
#include <raymath.h>
#include "ingame.hpp"
#include "../../main.hpp"
#include <iostream>


InGame::InGame(Config *config) : State(config)
{ 
    map = new Config{ config->windowWidth * 2, config->windowHeight * 2};
    monitor = GetCurrentMonitor();
    world = new Map(map->windowWidth, map->windowHeight);
    /*Create new Player*/
    player1 = Player(
        map,
        "Player 1",
        { 200.0, 200.0 },
        KeyboardKey::KEY_W,
        KeyboardKey::KEY_S,
        KeyboardKey::KEY_A,
        KeyboardKey::KEY_D,
        world
    );

    player2 = Player(
        map,
        "Player 2",
        { (float)(map->windowWidth - 200.0), (float)(map->windowHeight - 200.0) },
        KeyboardKey::KEY_UP,
        KeyboardKey::KEY_DOWN,
        KeyboardKey::KEY_LEFT,
        KeyboardKey::KEY_RIGHT,
        world
    );

    //ghost = Ghost("Ghost1", map);
    /*Create Camera*/
    camera = Camera2D{
        Vector2{(float) config->windowWidth / 2, (float) config->windowHeight / 2},
        {(float)map->windowWidth / 2, (float)map->windowHeight / 2 },
        0.0F, 0.5F
    };

    for (int i = 1; i <= 11; i++)
    {
        ghosts.push_back(Ghost("Ghost" + std::to_string(i), map));
    }

    nightVision = false;  /*disable flag by default*/
    displayCoordinates = false;  /*disable flag by default*/
    displayHitBoxes = false;    /*disable flag by default*/
    visionRadius = 30.0;
    /**/

    // get the locations of spots in shader
    char spotName[32] = "spots[x]\0";
    for (int i = 0; i < MAXSPOT; i++) {
        spotName[6] = '0' + i;
        spotLoc[i] = GetShaderLocation(spotShader, spotName);
    }

    spotPos[0].x = player1.getCenterPoint().x/ (map->windowWidth / config->windowWidth);
    spotPos[0].y = player1.getCenterPoint().y/ (map->windowHeight / config->windowHeight);
    spotPos[1].x = player2.getCenterPoint().x/2;
    spotPos[1].y = player2.getCenterPoint().y/2;

    

    /**/
}

InGame::~InGame()
{
}

inline void InGame::update()
{
    float dt = GetFrameTime();
    if (config->isUpdated) {
        map->windowWidth = config->windowWidth * 2;
        map->windowHeight = config->windowHeight * 2;
        world->scaleMapTexture(map->windowWidth, map->windowHeight);
    }

    player1.update();
    player2.update();
    //ghost.update();
    for (int i = 0; i < ghosts.size(); i++)
    {
        ghosts.at(i).update();

        if (!ghosts.at(i).isCaught) {
            if (CheckCollisionRecs(ghosts.at(i).getHitbox(), player1.getHitbox()))
            {
                ghosts.at(i).isCaught = true;
                ghosts.at(i).reloadTexture();
                player1score++;
            }
            if (CheckCollisionRecs(ghosts.at(i).getHitbox(), player2.getHitbox()))
            {
                ghosts.at(i).isCaught = true;
                ghosts.at(i).reloadTexture();
                player2score++;
            }
        }
    }

    if (IsKeyPressed(KEY_N)) nightVision = !nightVision; /*toggle flag*/
    if (IsKeyPressed(KEY_C)) displayCoordinates = !displayCoordinates; /*toggle flag*/
    if (IsKeyPressed(KEY_H)) displayHitBoxes = !displayHitBoxes; /*toggle flag*/




    /**/
        
        monitor = GetCurrentMonitor();
        spotPos[0].x = player1.getCenterPoint().x / (map->windowWidth / config->windowWidth);
        spotPos[0].y = config->windowHeight - player1.getCenterPoint().y / (map->windowHeight / config->windowHeight);
        spotPos[1].x = player2.getCenterPoint().x / (map->windowWidth / config->windowWidth);
        spotPos[1].y = config->windowHeight - player2.getCenterPoint().y / (map->windowHeight / config->windowHeight);
    
    SetShaderValue(spotShader, spotLoc[0], &spotPos[0].x, ShaderUniformDataType::SHADER_UNIFORM_VEC2);
    SetShaderValue(spotShader, spotLoc[1], &spotPos[1].x, ShaderUniformDataType::SHADER_UNIFORM_VEC2);
    
    /**/
}

inline void InGame::render()
{
    BeginMode2D(camera);
    ClearBackground(MAGENTA);
    world->render();
    player1.render();    /*Draw player model*/
    player2.render();

    for (int i = 0; i < ghosts.size(); i++)
    {
        ghosts.at(i).render();
    }

    if (displayHitBoxes)
    {
        DrawCircleLines(player1.getCenterPoint().x, player1.getCenterPoint().y, visionRadius*2, RED);
        DrawCircleLines(player2.getCenterPoint().x, player2.getCenterPoint().y, visionRadius*2, RED);
        DrawRectangleLinesEx(player1.getHitbox(), 2, RED);
        DrawRectangleLinesEx(player2.getHitbox(), 2, RED);
    }



    EndMode2D();

    if (!nightVision)
    {
        /*Shadow Experimental*/
        BeginShaderMode(spotShader);
        // instead of a blank rectangle you could render here
        // a render texture of the full screen used to do screen
        // scaling (slight adjustment to shader would be required
        // to actually pay attention to the colour!)
        DrawRectangle(0, 0, config->windowWidth, config->windowHeight, WHITE);
        EndShaderMode();
        /**/
    }

    if(displayCoordinates)
    {
        for (int i = 0; i < ghosts.size(); i++)
        {
            ghosts.at(i).displayDebugInfo(0, map->windowHeight / config->windowHeight, 10);
        }
        player1.displayDebugInfo(0);  /*Display coordinates*/
        player2.displayDebugInfo(60);  /*Display coordinates*/
        DrawText(TextFormat("%d", player1score), 400, 400, 20, RAYWHITE);
        DrawText(TextFormat("%d", player2score), 400, 440, 20, RAYWHITE);
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
