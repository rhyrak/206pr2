#include "entity.h"

Entity::Entity()
{
}

/*Accessor*/
Vector2 Entity::getCenterPoint() {
    return Vector2{ centerPoint.x,centerPoint.y };
}

/*For Debug purposes, display coordinates of entity*/
void Entity::displayDebugInfo()
{
    DrawText(&idDebug[0], (int)xDebug.x - 20, (int)xDebug.y - 25, 20, BLACK);
    DrawText(TextFormat("%.2f", centerPoint.x), (int)xDebug.x, (int)xDebug.y, 20, BLACK);
    DrawText("X: ", (int)xDebug.x - 20, (int)xDebug.y, 20, BLACK);
    DrawText(TextFormat("%.2f", centerPoint.y), (int)yDebug.x, (int)yDebug.y + 20, 20, BLACK);
    DrawText("Y: ", (int)yDebug.x - 20, (int)yDebug.y + 20, 20, BLACK);
}