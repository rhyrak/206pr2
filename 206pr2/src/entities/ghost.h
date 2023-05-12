
#ifndef GHOST_H
#define GHOST_H

#include <vector>
#include "entity.h"

class Ghost : public Entity {
private:
	Texture2D texture;
	int randomDir;
	float randomRange = 0.0;
	bool moveRight = false;
	bool moveLeft = false;
	bool moveUp = false;
	bool moveDown = false;
	void moveRandom();
public:
	Ghost();
	~Ghost();
	void update();
	void render();
};
#endif
