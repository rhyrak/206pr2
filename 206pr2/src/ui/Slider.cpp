#include "Slider.hpp"
#include "UiElements.hpp"

Slider::Slider(Rectangle barHitbox, float initialValue, Color tint)
{
	barHitbox.height = barHitbox.width * 5.0F / 48.0F;
	this->barHitbox = barHitbox;
	this->value = new float;
	*this->value = initialValue;
	this->btnHitbox = Rectangle{ barHitbox.x + barHitbox.width * (*value), barHitbox.y - barHitbox.height * 0.5F,
		barHitbox.width * 10.0F / 48.0F, barHitbox.height * 12.0F / 5.0F };
	this->btnHitbox.x -= btnHitbox.width / 2;
	this->tint = tint;

	this->barTexture = getTexture(SLIDER_BAR,barHitbox.width, barHitbox.height);
	this->btnTexture = getTexture(SLIDER_BUTTON, btnHitbox.width, btnHitbox.height);
}

// bar 48x5 btn 10x12
Slider::Slider(Rectangle barHitbox, float* value, Color tint)
{
	barHitbox.height = barHitbox.width * 5.0F / 48.0F;
	this->barHitbox = barHitbox;
	this->value = value;
	this->btnHitbox = Rectangle{ barHitbox.x + barHitbox.width * (*value), barHitbox.y - barHitbox.height * 0.5F,
		barHitbox.width * 10.0F / 48.0F, barHitbox.height * 12.0F / 5.0F };
	this->btnHitbox.x -= btnHitbox.width / 2;
	this->tint = tint;

	this->barTexture = getTexture(SLIDER_BAR, barHitbox.width, barHitbox.height);
	this->btnTexture = getTexture(SLIDER_BUTTON, btnHitbox.width, btnHitbox.height);
}

Slider::Slider()
{
	UnloadTexture(barTexture);
	UnloadTexture(btnTexture);
}

Slider::~Slider()
{

}

int Slider::render()
{
	// update logic inside render :/
	if ((IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), btnHitbox)) ||
		(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), barHitbox))) {
		*value = (GetMousePosition().x - barHitbox.x) / barHitbox.width;
		if (*value > 1)
			*value = 1;
		else if (*value < 0)
			*value = 0;
	}
	btnHitbox.x = barHitbox.x + barHitbox.width * (*value) - btnHitbox.width/2.5F;

	DrawTexture(barTexture, barHitbox.x, barHitbox.y, WHITE);

	bool hover = CheckCollisionPointRec(GetMousePosition(), btnHitbox);
	if (hover)
		DrawTexture(btnTexture, btnHitbox.x, btnHitbox.y, tint);
	else
		DrawTexture(btnTexture, btnHitbox.x, btnHitbox.y, WHITE);
	
	// uncomment for debugging
	//DrawText(TextFormat("%f", *value), barHitbox.x + barHitbox.width * 1.1, barHitbox.y, barHitbox.height, RED);

	return hover ? 1 : 0;
}


float Slider::getValue()
{
	return *value;
}