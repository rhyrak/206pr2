#include "IconButton.hpp"
#include "UiElements.hpp"

inline void setTexture(int icon, std::vector<Texture2D> *textures, float scale);

IconButton::IconButton(Rectangle hitbox, int icon, Color tint)
	: hitbox{ hitbox }, type{ icon }, tint { tint }
{
	signalF = new int;
	*signalF = -1;
	setTexture(icon, &textures, hitbox.width / 16.0F);
}


IconButton::IconButton()
{

}

IconButton::~IconButton()
{

}

void IconButton::scale(float scale)
{
	setTexture(type, &textures, scale);
}

void IconButton::setPosition(Vector2 newPos)
{
	this->hitbox.x = newPos.x;
	this->hitbox.y = newPos.y;
}

bool IconButton::render()
{
	if (CheckCollisionPointRec(GetMousePosition(),hitbox))
		DrawTexture(textures.at(0), hitbox.x, hitbox.y, tint);
	else
		DrawTexture(textures.at(0), hitbox.x, hitbox.y, WHITE);

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), hitbox))
		return true;
	return false;
}


inline void setTexture(int icon, std::vector<Texture2D> *textures, float scale) {
	if (!(*textures).empty() )
		(*textures).clear();
	
	switch (icon)
	{
	case I_GO_FULLSCREEN:
		*textures = std::vector<Texture2D>(1);
		(*textures).at(0) = getTexture(IBTN_FULLSCREEN, scale);
		break;
	case I_GO_WINDOWED:
		*textures = std::vector<Texture2D>(1);
		(*textures).at(0) = getTexture(IBTN_WINDOWED, scale);
		break;
	case I_EXIT:
		*textures = std::vector<Texture2D>(1);
		(*textures).at(0) = getTexture(IBTN_EXIT, scale);
		break;
	default:
		break;
	}
}