#include "map.hpp"
#include <iostream>
#include <raymath.h>
#include "../../main.hpp"

Image image = LoadImage("map.png");


inline void map::render()
{
int firstElement = arr[0][0][0];
std::cout << firstElement << std::endl;
}

 void initTileSet() {

    
   /* img = Image[2049];*/
    int iter = 1;
    for (int j = 0; j < 32; j++) {
        for (int i = 0; i < 64; i++) {

        }
    }
}

  void draw() {
    
        
    
 }

 bool canMove(int x, int y) {
    int xIndex = x / 64, yIndex = y / 64;
    bool canMove = true;

    for (int layer = 1; layer < sizeof(arr); layer++)
        try {
        if (arr[layer][yIndex][xIndex] > 0) {
            canMove = false;
            break;
        }
    }
    catch (...) {
        canMove = false;
    }

    return canMove;
}