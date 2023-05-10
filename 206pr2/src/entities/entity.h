
#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

class Entity
{
protected:
    Entity();
    Rectangle hitbox;
    Vector2 centerPoint = { 0 , 0 };
public:
    /*Temp for debug purposes*/
    Vector2 xDebug = { 0 , 0 };
    Vector2 yDebug = { 0 , 0 };
    Vector2 getCenterPoint();
    void displayDebugInfo();
};

#endif
