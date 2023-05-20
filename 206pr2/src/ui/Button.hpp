#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <raylib.h>

class Button
{
private:
	Rectangle hitbox;
	Texture2D texture;
	Color tint;
public:
	Button(Rectangle hitbox, const char* text, int fontSize, Color tint = GRAY);
	Button();
	~Button();
	int render();
	Rectangle getHitbox();
};

#endif