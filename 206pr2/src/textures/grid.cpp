#include "grid.hpp"

Grid::Grid()
{

}

Grid::Grid(Config* config)
{
	this->config = config;
	//texture = LoadTexture("res/black.png");
	this->size = 16;
	fillVector();
}

Grid::~Grid()
{

}

void Grid::fillVector()
{
	for (int i = 0; i < config->windowWidth / size; i++) {
		for (int j = 0; j < config->windowHeight / size; j++) {
			arr.push_back(Shadow({(float)i*size, (float)j*size}, (float)size, DARKGRAY));
		}
	}
}

void Grid::render(Vector2 coords) {
	coords = normalizeVector2(coords);
	getShadow(coords).render();
}

Shadow Grid::getShadow(Vector2 coords)
{
	int x = coords.x;
	int y = coords.y;
	return arr.at((y * (config->windowHeight / size)) + x);
}

Vector2 Grid::normalizeVector2(Vector2 coords)
{
	int x = (floor(coords.x) / size) * size;
	int y = (floor(coords.y) / size) * size;
	return { (float)x, (float)y };
}