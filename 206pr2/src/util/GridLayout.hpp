#ifndef GRID_LAYOUT_HPP
#define GRID_LAYOUT_HPP

#include "../../main.hpp"

class GridLayout
{
private:
	Config* config;
	float gridSize;
	int gridCountX;
	int gridCountY;
	bool useCount;
public:
	GridLayout(Config* config, float gridSize);
	GridLayout();
	~GridLayout();
	void drawGrid();
	float getGridSize();
	float getXCoord(float x);
	float getXCoordCentered(float x, float width);
	float getYCoordCentered(float y, float height);
	float getYCoord(float y);
	void recalculate();
};

#endif
