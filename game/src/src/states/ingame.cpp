#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <string>
#include "ingame.hpp"
#include "../../main.hpp"
#include "../map/map.hpp"
#include "../ui/UiElements.hpp"

#define MAX(a,b) (a > b ? a : b)
int player1roundWins = 0;
int player2roundWins = 0;

InGame::InGame(Config *config) : State(config)
{
    ghostDeath = LoadSound("game/res/ghostDeath.mp3");
    player1Sound = LoadSound("game/res/player1footstep.mp3");
    player2Sound = LoadSound("game/res/player2footstep.mp3");
    SetSoundVolume(player1Sound, config->sfxLevel);
    SetSoundVolume(player2Sound, (config->sfxLevel)/4);
    isPaused = false;
    incrementOnce = true;
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
        ghosts.push_back(Ghost("Ghost", map, world));
        /*Addition is overloaded, concatenate 'i' to idDebug of Ghost object*/
        ghosts.at(i) + (i+1);
    }

    for (int i = 0; i < 11; i++)
    {
        mushrooms.push_back(Mushroom("Mushroom", map, world));
        /*Addition is overloaded, concatenate 'i' to idDebug of Ghost object*/
        mushrooms.at(i) + (i + 1);
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
    remTime = 60; // seconds
    
    showScoreboard = false;

    pauseBtns.push_back(new IconButton(Rectangle{
        gl.getXCoord(1.0F), gl.getYCoord(1.0F), gl.getGridSize(), gl.getGridSize()}, I_ARROW_BACK));
    pauseBtns.push_back(new IconButton(Rectangle{
        gl.getXCoord(1.0F), gl.getYCoord(-2.0F), gl.getGridSize(), gl.getGridSize()}, I_GEAR));

    gameoverBg = getTexture(GAME_OVER_BG, gl.getGridSize() * 12, gl.getGridSize() * 6);
}

InGame::~InGame()
{
    std::cout << "****************************************************************************************************"
        "\n\t\t\tDESTRUCTING INGAME\n" <<
        "****************************************************************************************************\n";
    UnloadTexture(scoreboard);
    UnloadTexture(gameoverBg);
    UnloadSound(ghostDeath);
    UnloadSound(player1Sound);
    UnloadSound(player2Sound);
    for (int i = 0; i < pauseBtns.size(); i++)
        delete pauseBtns.at(i);
    pauseBtns.clear();
    delete world;
    player1score = 0;
    player2score = 0;
    player1roundWins = 0;
    player2roundWins = 0;
}

void InGame::reset()
{
    player1.reset();
    player2.reset();
    for (int i = 0; i < ghosts.size(); i++)
        ghosts.at(i).reset();
    for (int i = 0; i < mushrooms.size(); i++)
        mushrooms.at(i).reset();
    player1score = 0;
    player2score = 0;
    remTime = 60;
    incrementOnce = true;
}

inline void InGame::update()
{
    SetSoundVolume(player1Sound, config->sfxLevel);
    SetSoundVolume(player2Sound, (config->sfxLevel) / 4);
    SetSoundVolume(ghostDeath, config->sfxLevel);

    signalF = S_NO_CHANGE;
    if (remTime <= -5)
    {
        signalF = S_NAV_INGAME;
    }
    if (config->isUpdated) {
        map->windowWidth = config->windowWidth * 2;
        map->windowHeight = config->windowHeight * 2;
        world->scaleMapTexture(map->windowWidth, map->windowHeight);
    }

    config->cursorType = isPaused ? 1 : -1;
    if (!isPaused) remTime -= GetFrameTime();
    if (!isPaused && remTime > 0)
    {
        /*update players positions and play sfx*/
        player1.update();
        if (IsKeyPressed(player1.getUpKey()))
            PlaySound(player1Sound);
        if (IsKeyPressed(player1.getLeftKey()))
            PlaySound(player1Sound);
        if (IsKeyPressed(player1.getDownKey()))
            PlaySound(player1Sound);
        if (IsKeyPressed(player1.getRightKey()))
            PlaySound(player1Sound);

        player2.update();
        if (IsKeyPressed(player2.getUpKey()))
            PlaySound(player2Sound);
        if (IsKeyPressed(player2.getLeftKey()))
            PlaySound(player2Sound);
        if (IsKeyPressed(player2.getDownKey()))
            PlaySound(player2Sound);
        if (IsKeyPressed(player2.getRightKey()))
            PlaySound(player2Sound);

        /*update ghost positions and check for collision*/
        for (int i = 0; i < ghosts.size(); i++)
        {
            ghosts.at(i).update();

            if (!ghosts.at(i).isCaught) 
            {
                if (!player1.getStatus() && !player1.getPicking())
                {
                    if (CheckCollisionRecs(ghosts.at(i).getHitbox(), player1.getHitbox()))
                    {
                        ghosts.at(i).isCaught = true;
                        ghosts.at(i).reloadTexture();
                        player1score -= 3;
                        player1.changeSpeed(-50.0F);
                        player1.changePicking();
                        player1.resetAnimIndex();
                    }
                }

                if (!player2.getStatus() && !player2.getPicking())
                {
                    if (CheckCollisionRecs(ghosts.at(i).getHitbox(), player2.getHitbox()))
                    {
                        ghosts.at(i).isCaught = true;
                        ghosts.at(i).reloadTexture();
                        player2score -= 3;
                        player2.changeSpeed(-50.0F);
                        player2.changePicking();
                        player2.resetAnimIndex();
                    }
                }  
            }
            else if (!ghosts.at(i).soundPlayed)
            {
                PlaySound(ghostDeath);  /*play death sound*/
                ghosts.at(i).soundPlayed = true;    /*enable flag*/

            }
        }
        for (int i = 0; i < mushrooms.size(); i++)
        {
            mushrooms.at(i).update();

            if (!mushrooms.at(i).isCaught)
            {
                if (!player1.getStatus() && !player1.getPicking())
                {
                    if (CheckCollisionRecs(mushrooms.at(i).getHitbox(), player1.getHitbox()))
                    {
                        mushrooms.at(i).isCaught = true;
                        mushrooms.at(i).reloadTexture();
                        player1score += 5;
                        player1.changeSpeed(30.0F);
                        player1.changePicking();
                        player1.resetAnimIndex();
                    }
                }
                
                if (!player2.getStatus() && !player2.getPicking())
                {
                    if (CheckCollisionRecs(mushrooms.at(i).getHitbox(), player2.getHitbox()))
                    {
                        mushrooms.at(i).isCaught = true;
                        mushrooms.at(i).reloadTexture();
                        player2score += 5;
                        player2.changeSpeed(30.0F);
                        player2.changePicking();
                        player2.resetAnimIndex();
                    }
                }
            }
            else if (!mushrooms.at(i).soundPlayed)
            {
                PlaySound(ghostDeath);  /*play death sound*/
                mushrooms.at(i).soundPlayed = true;    /*enable flag*/
            }
        }
    }

    if (IsKeyPressed(KEY_N)) nightVision = !nightVision; /*toggle flag*/
    if (IsKeyPressed(KEY_C)) displayCoordinates = !displayCoordinates; /*toggle flag*/
    if (IsKeyPressed(KEY_H)) displayHitBoxes = !displayHitBoxes; /*toggle flag*/

    if (IsKeyPressed(KEY_P)) isPaused = !isPaused; // toggle pause
    if (IsKeyPressed(KEY_TAB)) showScoreboard = !showScoreboard;
    //if (IsKeyPressed(KEY_X)) signalF = S_NAV_PUSH_SETTINGS;
        
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

    for (int i = 0; i < ghosts.size(); i++)
    {
        ghosts.at(i).render();
    }

    for (int i = 0; i < mushrooms.size(); i++)
    {
        mushrooms.at(i).render();
    }

    player1.render();    /*Draw player model*/
    player2.render();

    if (displayHitBoxes)
    {
        DrawRectangleLinesEx(player1.getHitbox(), 2, RED);
        DrawRectangleLinesEx(player2.getHitbox(), 2, RED);
        for (int i = 0; i < ghosts.size(); i++)
        {
            DrawRectangleLinesEx(ghosts.at(i).getHitbox(), 2, RED);
        }
        for (int i = 0; i < mushrooms.size(); i++)
        {
            DrawRectangleLinesEx(mushrooms.at(i).getHitbox(), 2, RED);
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
        for (int i = 0; i < mushrooms.size(); i++)
        {
            mushrooms.at(i).displayDebugInfo(0, map->windowHeight / config->windowHeight, 10);
        }
        player1.displayDebugInfo(0);  /*Display coordinates*/
        player2.displayDebugInfo(60);  /*Display coordinates*/
        DrawText(TextFormat("%d", player1roundWins), 400, 400, 20, RAYWHITE);
        DrawText(TextFormat("%d", player2roundWins), 400, 440, 20, RAYWHITE);

    } 

    /*display scoreboard*/
    if (showScoreboard || isPaused)
    {
        if(isPaused)
            DrawRectangle(0, 0, config->windowWidth, config->windowHeight, Color{0,0,0,128});
        DrawTexture(scoreboard, gl.getXCoordCentered(16,scoreboard.width), gl.getYCoordCentered(1.25F,scoreboard.height), WHITE);
        const char* sbText = TextFormat("%02d %d %02d", player1score, MAX((int)remTime,0), player2score);
        Vector2 textDim = MeasureTextEx(font, sbText, gl.getGridSize() * 0.75F, 0);
        DrawTextEx(font, sbText, Vector2{ gl.getXCoordCentered(16, textDim.x), gl.getYCoordCentered(1.15F, textDim.y) },
            gl.getGridSize() * 0.75F, 0, UI_LIGHT_BROWN);
        //gl.drawGrid();
    }
    if (isPaused)
    {
        for (int i = 0; i < pauseBtns.size(); i++)
        {
            int feedback = pauseBtns.at(i)->render();
            if (feedback == 1) config->cursorType = 0;
            else if (feedback == 2) {
                switch (i)
                {
                case 0: signalF = S_NAV_MENU; break;
                case 1: signalF = S_NAV_PUSH_SETTINGS; break;
                }
            }
        }
    }
    if (remTime <= 0)
    {
        showScoreboard = true;
        DrawTexture(gameoverBg, gl.getXCoord(10), gl.getYCoord(2.5F), WHITE);
        if (player1score > player2score)
        {
            DrawText("PLAYER 1 WON",gl.getXCoord(12.35F), gl.getYCoord(3.5), gl.getGridSize(), UI_LIGHT_BROWN);
            if (incrementOnce)
            {
                player1roundWins++;
                incrementOnce = false;
            }
        }
        else if (player2score > player1score)
        {
            DrawText("PLAYER 2 WON", gl.getXCoord(12.35F), gl.getYCoord(3.5), gl.getGridSize(), UI_LIGHT_BROWN);
            if (incrementOnce)
            {
                player2roundWins++;
                incrementOnce = false;
            }
            
        }        
        else
            DrawText("IT IS A DRAW",gl.getXCoord(12.35F), gl.getYCoord(3.5), gl.getGridSize(), UI_LIGHT_BROWN);

        DrawText(TextFormat("NEW GAME IN %d", (int)(6 + remTime)),
            gl.getXCoord(12), gl.getYCoord(4.5), gl.getGridSize(), UI_LIGHT_BROWN);
        DrawText(TextFormat("P1: %d", player1roundWins),
            gl.getXCoord(13), gl.getYCoord(6), gl.getGridSize(), UI_LIGHT_BROWN);
        DrawText(TextFormat("P2: %d", player2roundWins),
            gl.getXCoord(17), gl.getYCoord(6), gl.getGridSize(), UI_LIGHT_BROWN);
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
