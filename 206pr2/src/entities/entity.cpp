#include "entity.h"

Entity::Entity()
{
}

/*Accessor*/
Vector2 Entity::getCenterPoint() {
    return Vector2{ centerPoint.x,centerPoint.y };
}

/*For Debug purposes, display coordinates of entity*/
void Entity::displayDebugInfo(int offset)
{
    DrawText(&idDebug[0], (int)xDebug.x + 5, (int)xDebug.y + offset, 20, BLUE);
    DrawText(TextFormat("%.2f", centerPoint.x), (int)xDebug.x + 25, (int)xDebug.y + offset + 20 , 20, BLUE);
    DrawText("X: ", (int)xDebug.x + 5, (int)xDebug.y + offset + 20, 20, BLUE);
    DrawText(TextFormat("%.2f", centerPoint.y), (int)yDebug.x + 25, (int)yDebug.y + offset + 40, 20, BLUE);
    DrawText("Y: ", (int)yDebug.x + 5, (int)yDebug.y + offset + 40, 20, BLUE);
}