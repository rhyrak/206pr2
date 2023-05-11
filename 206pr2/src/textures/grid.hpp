#pragma once

#include "raylib.h"
#include "../../main.h"
#include <vector>

class Grid
{
public:
	int size;
	Config* config;
	Texture2D texture;
	std::vector<Rectangle> arr;
	Grid();
	Grid(Config* config);
	void fillVector();
	void render(Vector2 coords);
	Rectangle getRectangle(Vector2 coords);

};