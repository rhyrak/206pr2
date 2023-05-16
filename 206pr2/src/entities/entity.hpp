
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
    Config* map;
public:
    Vector2 getCenterPoint();
    virtual Texture2D getTexture(const char* path);
    Texture2D texture;
    Image missingTexture;
    /*Temp for debug purposes*/
    std::string idDebug;
    Vector2 DebugXY = { 0 , 0 };
    void displayDebugInfo(int offset, int = 1, int = 20);
    /*^^^^^^^^^^^^^^^^^^^^^^^*/
};

#endif
