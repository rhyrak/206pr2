#include "entity.h"

Entity::Entity()
{
}

Vector2 Entity::getCenterPoint() {
    return Vector2{ centerPoint.x,centerPoint.y };
}

void Entity::displayDebugInfo()
{
    DrawText("Player 1's coordinates:", (int)xDebug.x, (int)xDebug.y - 25, 20, BLACK);
    DrawText(TextFormat("%.2f", centerPoint.x), (int)xDebug.x, (int)xDebug.y, 20, BLACK);
    DrawText(TextFormat("%.2f", centerPoint.y), (int)yDebug.x, (int)yDebug.y + 20, 20, BLACK);
}