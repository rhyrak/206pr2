#include "map.hpp"
#include <iostream>
#include <raymath.h>
#include "../../main.hpp"
#include "mapData.hpp"

int TileWidth;
int TileHeight;

Map::Map(int w, int h)
{
    this->height = h;
    this->width = w;
    scaleMapTexture(w, h);
}

Map::~Map()
{
    std::cout << "\nMAP DESTRUCTOR\n";
    UnloadTexture(mapTexture);
}

Map::Map()
{

}

void Map::render()
{
    DrawTexture(mapTexture, 0, 0, WHITE);
}

void Map::scaleMapTexture(int w, int h) {
     this->tileWidth = w / 32;
     this->tileHeight = h / 18;
     TileWidth = this->tileWidth;
     TileHeight = this->tileHeight;
     UnloadTexture(mapTexture);
     Image mapImg = GenImageColor(w, h, MAGENTA);
    Image tileSet = LoadImage("game/res/map.png");
    std::vector<Image> tiles = std::vector<Image>(2500);
    tiles.at(0) = GenImageColor(this->tileWidth, this->tileHeight, Color{0,0,0,0});
    int iter = 1;
    for (int j = 0; j < 31; j++) {
        for (int i = 0; i < 64; i++) {
            Image tile = ImageFromImage(tileSet, Rectangle{ 16.0F * i,16.0F * j,16,16 });
            ImageResizeNN(&tile, this->tileWidth, this->tileHeight);
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
                ImageDraw(&mapImg, tiles[mapData[layer][y][x]], Rectangle{ 0,0,(float)tileWidth,(float)tileHeight }, Rectangle{ x * (float)tileWidth, y * (float)tileHeight, (float)tileWidth, (float)tileHeight }, LIGHTGRAY);
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
    int xIndex = x / (width / 32), yIndex = y / (height / 18);
    bool canMove = false;
        try {
        if (mapData[0][(int)floor(yIndex)][(int)floor(xIndex)] != 0 && mapData[2][(int)floor(yIndex)][(int)floor(xIndex)] != 1248) {
            canMove = true;
        }
    }
    catch (...) {
        canMove = false;
    }

    return canMove;
}

int Map::getTileWidth()
{
    return tileWidth;
}

int Map::getTileHeight()
{
    return tileHeight;
}