#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <raylib.h>

class Slider
{
private:
	Rectangle barHitbox; // <---------->
	Rectangle btnHitbox; // []             bar + btn = <------[]---> (70%)
	Texture2D barTexture;
	Texture2D btnTexture;
	Color tint;
	float *value;
public:
	Slider(Rectangle barHitbox, float initialValue, Color tint = GRAY);
	Slider(Rectangle barHitbox, float *value, Color tint = GRAY);
	Slider();
	~Slider();
	int render();
	float getValue();
};

#endif
