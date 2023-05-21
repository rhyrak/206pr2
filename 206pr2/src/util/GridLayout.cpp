#include "GridLayout.hpp"

GridLayout::GridLayout(int width, int height, float gridSize) : width{width}, height{height}
{
	if (gridSize > 0)
	{
		this->gridSize = gridSize;
		useCount = false;
		gridCountX = width / gridSize;
		gridCountY = height / gridSize;
	}
	else
	{
		gridCountX = -gridSize;
		useCount = true;
		this->gridSize = width / gridCountX;
		gridCountY = height / gridSize;
	}
}

GridLayout::GridLayout() : width{0}, height{0}, gridCountX{0}, gridCountY{0}, gridSize{0}, useCount{false}
{
}

GridLayout::~GridLayout()
{
}


void GridLayout::recalculate(int width, int height)
{
	this->width = width;
	this->height = height;
	if (useCount) {
		gridSize = width / (float)gridCountX;
	}
	else
	{
		gridCountX = width / gridSize;
		gridCountY = height / gridSize;
	}
}

void GridLayout::drawGrid()
{

	for (int i = 0; i*gridSize < height; i++)
	{
		DrawLine(0, i * gridSize, width, i * gridSize, Color{ 255,0,0,60 });
		if (i%5 == 0)
			DrawLine(0, i * gridSize, width, i * gridSize, Color{ 255,0,0,155 });
	}
	for (int i = 0; i * gridSize < width; i++)
	{
		DrawLine(i * gridSize, 0, i * gridSize, width, Color{ 255,0,0,60 });
		if (i % 5 == 0)
			DrawLine(i * gridSize, 0, i * gridSize, width, Color{ 255,0,0,155 });
	}
}

float GridLayout::getXCoord(float x) {
	return x * gridSize;
}

float GridLayout::getYCoord(float y) {
	return y * gridSize;
}

float GridLayout::getXCoordCentered(float xIndex, float width) {
	return xIndex * gridSize - width/2;
}

float GridLayout::getYCoordCentered(float yIndex, float height) {
	return yIndex * gridSize - height/2;
}

float GridLayout::getGridSize()
{
	return gridSize;
}
