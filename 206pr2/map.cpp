#include "map.hpp"
#include <iostream>
#include <raymath.h>
#include "../../main.hpp"

Image image = LoadImage("map.png");
void map::AddImage(Image image) {
	floor.push_back(image);
}

Image map::GetImage(int index) {
	return floor[index];
}

inline void map::render()
{
int firsElement = arr[0][0][0];
std::cout << firsElement << std::endl;
}