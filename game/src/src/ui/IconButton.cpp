#include "IconButton.hpp"
#include "UiElements.hpp"

inline void setTexture(int icon,Texture2D *texture, float scale);

IconButton::IconButton(Rectangle hitbox, int icon, Color tint)
	: hitbox{ hitbox }, type{ icon }, tint { tint }
{
	signalF = new int;
	*signalF = -1;
	setTexture(icon, &texture, hitbox.width / 16.0F);
}

IconButton::~IconButton()
{
	delete signalF;
	UnloadTexture(texture);
}

void IconButton::scale(float scale)
{
	setTexture(type, &texture, scale);
}

void IconButton::setPosition(Vector2 newPos)
{
	this->hitbox.x = newPos.x;
	this->hitbox.y = newPos.y;
}

int IconButton::render()
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

Rectangle IconButton::getHitbox() {
	return Rectangle{ hitbox.x, hitbox.y, hitbox.width, hitbox.height };
}


inline void setTexture(int icon, Texture2D *texture, float scale) {
	if (IsTextureReady(*texture))
		UnloadTexture(*texture);
	
	switch (icon)
	{
	case I_GO_FULLSCREEN:
	{
		*texture = getTexture(IBTN_FULLSCREEN, scale);
		break;
	}
	case I_GO_WINDOWED:
	{
		*texture = getTexture(IBTN_WINDOWED, scale);
		break;
	}
	case I_EXIT:
	{
		*texture = getTexture(IBTN_EXIT, scale);
		break;
	}
	case KEY_UP:
	case KEY_LEFT:
	case KEY_RIGHT:
	case KEY_DOWN:
		{
			Image temp = LoadImageFromTexture(getTexture(IBTN_EMTPY, 1));
			Image arrow = LoadImageFromTexture(getTexture(UP_ARROW, 1));
			ImageDraw(&temp, arrow, Rectangle{ 0,0,16,16 }, Rectangle{ 0,0,16,16 }, WHITE);
			if (icon == KEY_DOWN)
				ImageFlipVertical(&temp);
			if (icon == KEY_LEFT)
				ImageRotateCCW(&temp);
			if (icon == KEY_RIGHT)
				ImageRotateCW(&temp);
			ImageResizeNN(&temp, temp.width * scale, temp.height * scale);
			*texture = LoadTextureFromImage(temp);
			UnloadImage(temp);
			UnloadImage(arrow);
			break;
		}
		
	case I_ARROW_BACK:
		{
			*texture = getTexture(ARROW_BACK,scale);
			break;
		}
		
	case I_GEAR:
		{
			*texture = getTexture(GEAR_ICON, scale);
			break;
		}
		
	default:
		{
			if ((icon >= 'a' && icon <= 'z') || (icon >= 'A' && icon <= 'Z') || (icon >= '0' && icon <= '9')) {
				Image temp = LoadImageFromTexture(getTexture(IBTN_EMTPY, scale));
				Image text = ImageText(TextFormat("%c", icon), temp.width * 0.65, UI_DARK_BROWN);
				ImageDraw(&temp, text, Rectangle{ 0,0,(float)text.width, (float)text.height }, Rectangle{ temp.width * 0.25F,temp.height * 0.25F,temp.width * 0.5F,temp.height * 0.5F },WHITE);
				*texture = LoadTextureFromImage(temp);
				UnloadImage(temp);
				UnloadImage(text);
			}
			else
			{
				*texture = getTexture(IBTN_EMTPY, scale);
			}
			break;
		}
	}
}