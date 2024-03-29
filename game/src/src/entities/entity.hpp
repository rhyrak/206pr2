
#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>
#include <string>
#include "../../main.hpp"

class Entity
{
protected:
    Entity();
    Rectangle hitbox;
    Vector2 centerPoint = { 0 , 0 };
    Vector2 centerPointC = { 0, 0 };
    Config* map;
    float speed = 1.0;
    float speedC = 1.0;
public:
    Vector2 getCenterPoint();
    virtual Texture2D getTexture(const char* path, int tileWidth, int tileHeight);
    virtual void reset();
    Texture2D texture;
    Image *image;
    /*Temp for debug purposes*/
    std::string idDebug;
    Vector2 DebugXY = { 0 , 0 };
    void displayDebugInfo(int offset, int = 1, int = 20);
    /*^^^^^^^^^^^^^^^^^^^^^^^*/
};

#endif
