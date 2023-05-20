#include "Button.hpp"
#include "UiElements.hpp"
#include <iostream>
#include "../../main.hpp"

Button::Button(Rectangle hitbox, const char* text, int fontSize, Color tint) :
	hitbox{hitbox}, tint{tint}
{
	Image temp = LoadImageFromTexture(getTexture(BTN_BROWN_ACTIVE,hitbox.height/16.0F));
	ImageResizeNN(&temp, hitbox.width, hitbox.height);
	Image textImg = ImageText(text, fontSize, UI_LIGHT_BROWN);
	ImageDraw(&temp, textImg, Rectangle{ 0,0,(float)textImg.width,(float)textImg.height },
		Rectangle{ temp.width/2.0F - textImg.width/2.0F, temp.height / 2.0F - textImg.height / 2.0F, (float)textImg.width, (float)textImg.height }, WHITE);
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