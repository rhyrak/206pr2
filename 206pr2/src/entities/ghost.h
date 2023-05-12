
#ifndef GHOST_H
#define GHOST_H

#include <vector>
#include "entity.h"

class Ghost : public Entity {
private:
	Texture2D texture;
	int actionLockCounter = 0;
	bool moveRight = false;
	bool moveLeft = false;
	bool moveUp = false;
	bool moveDown = false;
	void move();
public:
	Ghost();
	Ghost(Vector2 coords);
	~Ghost();
	void update();
	void render();
};
#endif
