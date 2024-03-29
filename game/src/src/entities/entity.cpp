#include "entity.hpp"

Entity::Entity()
{
}

/*Accessor*/
Vector2 Entity::getCenterPoint() {
    return Vector2{ centerPoint.x,centerPoint.y };
}


Texture2D Entity::getTexture(const char* path, int tileWidth, int tileHeight)
{
    try {
        image = new Image;
        *image = LoadImage(path);
        if (!IsImageReady(*image)) throw 1;
        ImageResize(image, tileWidth * ScaleFactor, tileHeight * ScaleFactor);
        texture = LoadTextureFromImage(*image);
        UnloadImage(*image);
        return texture;
    }
    catch (...) {
        *image = GenImageChecked(64, 64, 32, 32, PURPLE, BLACK);
        ImageResize(image, tileWidth * ScaleFactor, tileHeight * ScaleFactor);
        texture = LoadTextureFromImage(*image);
        UnloadImage(*image);
        return texture;
    }
}

/*For Debug purposes, display coordinates of entity*/
void Entity::displayDebugInfo(int offset, int factor, int fontSize)
{
    DrawText(&idDebug[0], (int)(DebugXY.x+5)/factor, (int)(DebugXY.y+offset)/factor, fontSize, RAYWHITE);
    DrawText(TextFormat("%.2f", centerPoint.x), (int)(DebugXY.x + 25)/factor, (int)(DebugXY.y+offset+20)/factor , fontSize, RAYWHITE);
    DrawText("X: ", (int)(DebugXY.x+5)/factor, (int)(DebugXY.y+offset+20)/factor, fontSize, RAYWHITE);
    DrawText(TextFormat("%.2f", centerPoint.y), (int)(DebugXY.x+25)/factor, (int)(DebugXY.y+offset+40)/factor, fontSize, RAYWHITE);
    DrawText("Y: ", (int)(DebugXY.x+5)/factor, (int)(DebugXY.y+offset+40)/factor, fontSize, RAYWHITE);
}

void Entity::reset()
{

}