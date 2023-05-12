
#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>
#include <string>
#include "../../main.h"

class Entity
{
protected:
    Entity();
    Rectangle hitbox;
    Vector2 centerPoint = { 0 , 0 };
    Config* map;
public:
    Vector2 getCenterPoint();
    /*Temp for debug purposes*/
    std::string idDebug;
    Vector2 xDebug = { 0 , 0 };
    Vector2 yDebug = { 0 , 0 };
    void displayDebugInfo();
    /*^^^^^^^^^^^^^^^^^^^^^^^*/
};

#endif
