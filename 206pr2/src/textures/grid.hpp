#pragma once

#include "raylib.h"
#include "../../main.hpp"
#include "shadow.hpp"
#include <vector>

class Grid
{
public:
	int size;
	Config* config;
	std::vector<Shadow> arr;
	Grid();
	Grid(Config* config);
	~Grid();
	void fillVector();
	void render(Vector2 coords);
	Shadow getShadow(Vector2 coords);
	Vector2 normalizeVector2(Vector2 coords);

};