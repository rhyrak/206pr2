#include "UiElements.hpp"

Texture2D getTexture(UiElement uiElem, float scale) {
	Image uiPng = LoadImage("res/ui/ui.png");
	Image el = ImageFromImage(uiPng,uiElem);
	ImageResizeNN(&el, el.width * scale, el.height * scale);
	Texture2D texture = LoadTextureFromImage(el);
	UnloadImage(el);
	UnloadImage(uiPng);
	return texture;
}