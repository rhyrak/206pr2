#include "shadow.hpp"

Shadow::Shadow()
{
	
}

Shadow::Shadow(Vector2 coords, float size, Color color)
{
	shape = Rectangle{ coords.x, coords.y, size, size };
	this->size = size;
	this->color = color;
}

Shadow::~Shadow()
{

}

void Shadow::render() {
	DrawRectangleRec(shape, color);
}