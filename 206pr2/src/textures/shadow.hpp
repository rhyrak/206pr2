#pragma once

#include "raylib.h"

class Shadow 
{
public:
	Shadow();
	Shadow(Vector2 coords, float size, Color color);
	~Shadow();
	Color color;
	Rectangle shape;
	float size;
	void render();
};