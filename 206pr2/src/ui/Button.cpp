#include "Button.hpp"
#include "UiElements.hpp"
#include <iostream>

Button::Button(Rectangle hitbox, const char* text, Color tint) :
	hitbox{hitbox}, tint{tint}
{
	Image temp = LoadImageFromTexture(getTexture(BTN_BLUE_ACTIVE,hitbox.height/16.0F));
	ImageResizeNN(&temp, hitbox.width, hitbox.height);
	Image textImg = ImageText(text, temp.height*0.5, WHITE);
	ImageDraw(&temp, textImg, Rectangle{ 0,0,(float)textImg.width,(float)textImg.height },
		Rectangle{temp.width*0.10F,temp.height*0.15F,temp.width*0.8F,temp.height*0.7F }, WHITE);
	texture = LoadTextureFromImage(temp);
	UnloadImage(temp);
	UnloadImage(textImg);
}

Button::Button()
{
}

Button::~Button()
{
	UnloadTexture(texture);
}


int Button::render()
{
	bool hover = CheckCollisionPointRec(GetMousePosition(), hitbox);
	if (hover)
		DrawTexture(texture, hitbox.x, hitbox.y, tint);
	else
		DrawTexture(texture, hitbox.x, hitbox.y, WHITE);

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), hitbox))
		return 2;

	return hover ? 1 : 0;
}

Rectangle Button::getHitbox()
{
	return hitbox;
}