#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <vector>
#include <string>
#include "entity.hpp"
#include "../map/map.hpp"
class Mushroom : public Entity {
private:
	Texture2D texture;
	enum direction {LEFT, RIGHT, UP, DOWN};
	int textureWidth = 72, textureHeight = 72;
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
	Mushroom();
	Mushroom(std::string idDebug, Config* config, Map* world);
	~Mushroom();
	void update();
	void render();
	Rectangle getHitbox();
	bool isCaught;
	void reloadTexture();
	void reloadTextureC();
	void reset() override;
	Vector2 generateRandomCoordinates();
	bool soundPlayed = false;
	void operator + (const int& n);
};
#endif