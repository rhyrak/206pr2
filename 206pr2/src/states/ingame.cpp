#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <string>
#include "ingame.hpp"
#include "../../main.hpp"
#include "../map/map.hpp"
#include "../ui/UiElements.hpp"


InGame::InGame(Config *config) : State(config)
{
    isPaused = false;
    map = new Config;
    map->windowWidth = config->windowWidth * 2;
    map->windowHeight = config->windowHeight * 2;
    monitor = GetCurrentMonitor();
    world = new Map(map->windowWidth, map->windowHeight);
    /*Create new Player*/
    player1 = Player(
        map,
        "Player 1",
        { 200.0, 200.0 },
        &config->keymap.p1Up,
        &config->keymap.p1Down,
        &config->keymap.p1Left,
        &config->keymap.p1Right,
        world
    );

    player2 = Player(
        map,
        "Player 2",
        { (float)(map->windowWidth - 200.0), (float)(map->windowHeight - 200.0) },
        &config->keymap.p2Up,
        &config->keymap.p2Down,
        &config->keymap.p2Left,
        &config->keymap.p2Right,
        world
    );

    /*Create Camera*/
    camera = Camera2D{
        Vector2{(float) config->windowWidth / 2, (float) config->windowHeight / 2},
        {(float)map->windowWidth / 2, (float)map->windowHeight / 2 },
        0.0F, 0.5F
    };

    for (int i = 0; i < 11; i++)
    {
        ghosts.push_back(Ghost("Ghost", map));
        /*Addition is overloaded, concatenate 'i' to idDebug of Ghost object*/
        ghosts.at(i) + (i+1);
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

    /*set initial spotlight position to players coordinates*/
    spotPos[0].x = player1.getCenterPoint().x / (map->windowWidth / config->windowWidth);
    spotPos[0].y = player1.getCenterPoint().y / (map->windowHeight / config->windowHeight);
    spotPos[1].x = player2.getCenterPoint().x / (map->windowWidth / config->windowWidth);
    spotPos[1].y = player2.getCenterPoint().y / (map->windowHeight / config->windowHeight);

    gl = GridLayout(config->windowWidth, config->windowHeight, -32);
    scoreboard = getTexture(SCOREBOARD, 1.2F*gl.getGridSize()/16);
    remTime = 120; // seconds
}

InGame::~InGame()
{
    UnloadTexture(scoreboard);
}

inline void InGame::update()
{
    signalF = S_NO_CHANGE;
    if (config->isUpdated) {
        map->windowWidth = config->windowWidth * 2;
        map->windowHeight = config->windowHeight * 2;
        world->scaleMapTexture(map->windowWidth, map->windowHeight);
    }

    config->cursorType = isPaused ? 1 : -1;

    if (!isPaused)
    {
        remTime -= GetFrameTime();
        player1.update();
        player2.update();
        /*update ghost positions and check for collision*/
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
    }

    if (IsKeyPressed(KEY_N)) nightVision = !nightVision; /*toggle flag*/
    if (IsKeyPressed(KEY_C)) displayCoordinates = !displayCoordinates; /*toggle flag*/
    if (IsKeyPressed(KEY_H)) displayHitBoxes = !displayHitBoxes; /*toggle flag*/

    if (IsKeyPressed(KEY_P)) isPaused = !isPaused; // toggle pause
    if (IsKeyPressed(KEY_X)) signalF = S_NAV_PUSH_SETTINGS;
        
    /*track spotlights*/
    monitor = GetCurrentMonitor();
    spotPos[0].x = player1.getCenterPoint().x / (map->windowWidth / config->windowWidth);
    spotPos[0].y = config->windowHeight - player1.getCenterPoint().y / (map->windowHeight / config->windowHeight);
    spotPos[1].x = player2.getCenterPoint().x / (map->windowWidth / config->windowWidth);
    spotPos[1].y = config->windowHeight - player2.getCenterPoint().y / (map->windowHeight / config->windowHeight);
    SetShaderValue(spotShader, spotLoc[0], &spotPos[0].x, ShaderUniformDataType::SHADER_UNIFORM_VEC2);
    SetShaderValue(spotShader, spotLoc[1], &spotPos[1].x, ShaderUniformDataType::SHADER_UNIFORM_VEC2);
    
}

inline void InGame::render()
{
    BeginMode2D(camera);
    ClearBackground(MAGENTA);
    world->render();
    player1.render();    /*Draw player model*/
    player2.render();
    /*Draw ghosts*/
    for (int i = 0; i < ghosts.size(); i++)
    {
        ghosts.at(i).render();
    }

    if (displayHitBoxes)
    {
        DrawRectangleLinesEx(player1.getHitbox(), 2, RED);
        DrawRectangleLinesEx(player2.getHitbox(), 2, RED);
        for (int i = 0; i < ghosts.size(); i++)
        {
            DrawRectangleLinesEx(ghosts.at(i).getHitbox(), 2, RED);
        }
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

    /*display scoreboard*/
    if (IsKeyDown(KEY_TAB) || isPaused)
    {
        DrawTexture(scoreboard, gl.getXCoordCentered(16,scoreboard.width), gl.getYCoordCentered(1.25F,scoreboard.height), WHITE);
        const char* sbText = TextFormat("%02d %d %02d", player1score, (int)remTime, player2score);
        Vector2 textDim = MeasureTextEx(font, sbText, gl.getGridSize() * 0.75F, 0);
        DrawTextEx(font, sbText, Vector2{ gl.getXCoordCentered(16, textDim.x), gl.getYCoordCentered(1.15F, textDim.y) },
            gl.getGridSize() * 0.75F, 0, UI_LIGHT_BROWN);
        gl.drawGrid();
    }
    if (isPaused)
    {
        DrawText("PAUSED", gl.getXCoord(15), gl.getYCoord(5), gl.getGridSize(), BROWN);
        DrawText("PRESS X(WIP)", gl.getXCoord(16), gl.getYCoord(6), gl.getGridSize(), BROWN);
    }
}

/*Accessor*/
Signal InGame::signal()
{
    return signalF;
}

/*Accessor*/
Player InGame::getPlayer()
{
    return player1;
}
