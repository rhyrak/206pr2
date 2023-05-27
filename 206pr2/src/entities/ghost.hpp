
#ifndef GHOST_H
#define GHOST_H

#include <vector>
#include <string>
#include "entity.hpp"
#include "../map/map.hpp"
class Ghost : public Entity {
private:
	Texture2D texture;
	int textureWidth = 58, textureHeight = 76;
	enum direction { LEFT, RIGHT, UP, DOWN };
	direction dir;
	int animIndex = 0;
	float animTick = 0.0;
	int randomDir;
	float randomRange = 0.0;
	bool moveRight = false;
	bool moveLeft = false;
	bool moveUp = false;
	bool moveDown = false;
	Map* world;
	void moveRandom();
public:
	Ghost();
	Ghost(std::string idDebug, Config *config, Map *world);
	~Ghost();
	void update();
	void render();
	Rectangle getHitbox();
	bool isCaught;
	void reloadTexture();
	bool soundPlayed = false;
	void operator + (const int& n);
};
#endif
