#include "map.hpp"
#include <iostream>
#include <raymath.h>
#include "../../main.hpp"
#include "mapData.hpp"

Map::Map(int w, int h)
{
    scaleMapTexture(w, h);
}

Map::~Map()
{

}

Map::Map()
{

}

void Map::render()
{
    DrawTexture(mapTexture, 0, 0, WHITE);
}

 void Map::scaleMapTexture(int w, int h) {
     int tileWidth = w / 32;
     int tileHeight = h / 18;
     UnloadTexture(mapTexture);
     Image mapImg = GenImageColor(w, h, MAGENTA);
    Image tileSet = LoadImage("res/map.png");
    std::vector<Image> tiles = std::vector<Image>(2500);
    tiles.at(0) = GenImageColor(tileWidth, tileHeight, Color{0,0,0,0});
    int iter = 1;
    for (int j = 0; j < 31; j++) {
        for (int i = 0; i < 64; i++) {
            Image tile = ImageFromImage(tileSet, Rectangle{ 16.0F * i,16.0F * j,16,16 });
            ImageResizeNN(&tile, tileWidth, tileHeight);
            tiles.at(iter) = tile;
            iter++;
        }
    }

    for (int layer = 0; layer < 4 ; layer++)
    {
        for (int y = 0; y < 18; y++)
        {
            for (int x = 0; x < 32; x++)
            {
                if(mapData[layer][y][x] != 0 )
                ImageDraw(&mapImg, tiles[mapData[layer][y][x]], Rectangle{ 0,0,(float)tileWidth,(float)tileHeight }, Rectangle{ x * (float)tileWidth, y * (float)tileHeight, (float)tileWidth, (float)tileHeight }, WHITE);
                //ImageDrawText(&mapImg, TextFormat("%d", mapData[layer][y][x]), x * (float)tileWidth, y * (float)tileHeight,19,WHITE);
            }
        }
    }

    mapTexture = LoadTextureFromImage(mapImg);
    UnloadImage(mapImg);
    UnloadImage(tileSet);
    while (iter > 0)
        UnloadImage(tiles[iter--]);
}


bool Map::canMove(int x, int y) {
    int xIndex = x / 32, yIndex = y / 32;
    bool canMove = true;

    for (int layer = 1; layer < 4; layer++)
        try {
        if (mapData[layer][yIndex][xIndex] > 0) {
            canMove = false;
            break;
        }
    }
    catch (...) {
        canMove = false;
    }

    return canMove;
}