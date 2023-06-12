#ifndef GRID_LAYOUT_HPP
#define GRID_LAYOUT_HPP

#include "../../main.hpp"

class GridLayout
{
private:
	int width;
	int height;
	int gridCountX = 0;
	int gridCountY = 0;
	float gridSize = 0;
	bool useCount = false;
public:
	GridLayout(int width, int height, float gridSize);
	GridLayout();
	~GridLayout();
	void drawGrid();
	float getGridSize();
	float getXCoord(float x);
	float getXCoordCentered(float xIndex, float width);
	float getYCoordCentered(float yIndex, float height);
	float getYCoord(float y);
	void recalculate(int width, int height);
};

#endif
