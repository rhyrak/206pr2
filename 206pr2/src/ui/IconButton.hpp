#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <raylib.h>
#include <vector>

#define I_GO_FULLSCREEN 0
#define I_GO_WINDOWED 1
#define I_EXIT 2

class IconButton
{
private:
	Rectangle hitbox;
	std::vector<Texture2D> textures;
	int *signalF;
	int type;
	Color tint;
public:
	IconButton(Rectangle hitbox, int icon, Color tint = GRAY);
	~IconButton();
	void scale(float scale);
	void setPosition(Vector2 newPos);
	int render();
};

#endif
