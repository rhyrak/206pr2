#include "GridLayout.hpp"

GridLayout::GridLayout(Config* config, float gridSize)
{
	this->config = config;
	if (gridSize > 0)
	{
		this->gridSize = gridSize;
		useCount = false;
		gridCountX = config->windowWidth / gridSize;
		gridCountY = config->windowHeight / gridSize;
	}
	else
	{
		gridCountX = -gridSize;
		useCount = true;
		this->gridSize = config->windowWidth / gridCountX;
		gridCountY = config->windowHeight / gridSize;
	}
}

GridLayout::GridLayout()
{
}

GridLayout::~GridLayout()
{
}


void GridLayout::recalculate()
{
	if (useCount) {
		gridSize = config->windowWidth / gridCountX;
	}
	else
	{
		gridCountX = config->windowWidth / gridSize;
		gridCountY = config->windowHeight / gridSize;
	}
}

void GridLayout::drawGrid()
{

	for (int i = 0; i*gridSize < config->windowHeight; i++)
	{
		DrawLine(0, i * gridSize, config->windowWidth, i * gridSize, Color{ 255,0,0,60 });
	}
	for (int i = 0; i * gridSize < config->windowWidth; i++)
	{
		DrawLine(i * gridSize, 0, i * gridSize, config->windowWidth, Color{ 255,0,0,60 });
	}
}

float GridLayout::getXCoord(float x) {
	return (int)(x * gridSize + 0.5F);
}

float GridLayout::getYCoord(float y) {
	return (int)(y * gridSize + 0.5F);
}


float GridLayout::getXCoordCentered(float x, float width) {
	return x * gridSize - width/2;
}

float GridLayout::getYCoordCentered(float y, float height) {
	return y * gridSize - height/2;
}


float GridLayout::getGridSize()
{
	return gridSize;
}
