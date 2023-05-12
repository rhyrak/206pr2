#include "grid.hpp"

Grid::Grid()
{
}

Grid::Grid(Config* config)
{
	this->config = config;
	texture = LoadTexture("res/black.png");
	this->size = texture.height;
	fillVector();
}

void Grid::fillVector()
{
	for (int i = 0; i < config->windowWidth / size; i++) {
		for (int j = 0; j < config->windowHeight / size; j++) {
			arr.push_back(Rectangle{(float)i*size, (float)j*size, (float)size, (float)size});
		}
	}
}

void Grid::render(Vector2 coords) {
	int x = (floor(coords.x) / size) * size;
	int y = (floor(coords.y) / size) * size;
	DrawTexture(texture, x, y, WHITE);
}

Rectangle Grid::getRectangle(Vector2 coords)
{
	int x = coords.x;
	int y = coords.y;
	return arr.at((y * (config->windowHeight / size)) + x);
}