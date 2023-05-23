#include "UiElements.hpp"

Texture2D getTexture(UiElement uiElem, float scale) {
	Image uiPng = LoadImage("res/ui/ui.png");
	if (!IsImageReady(uiPng) || uiElem.width == 0 || uiElem.height == 0)
		return LoadTextureFromImage(GenImageChecked(16 * scale, 16 * scale, 16 * scale, 16 * scale, MAGENTA, BLACK));

	Image el = ImageFromImage(uiPng, uiElem);
	if (!IsImageReady(el)) {
		UnloadImage(uiPng);
		return LoadTextureFromImage(GenImageChecked(16 * scale, 16 * scale, 16 * scale, 16 * scale, MAGENTA, BLACK));
	}

	ImageResizeNN(&el, el.width * scale, el.height * scale);
	Texture2D texture = LoadTextureFromImage(el);
	if (!IsTextureReady(texture)) {
		UnloadImage(el);
		UnloadImage(uiPng);
		return LoadTextureFromImage(GenImageChecked(16 * scale, 16 * scale, 16 * scale, 16 * scale, MAGENTA, BLACK));
	}

	UnloadImage(el);
	UnloadImage(uiPng);
	return texture;
}


Texture2D getTexture(UiElement uiElem, float width, float height) {
	Image uiPng = LoadImage("res/ui/ui.png");
	if (!IsImageReady(uiPng) || uiElem.width == 0 || uiElem.height == 0)
		return LoadTextureFromImage(GenImageChecked(width, height, 2, 2, MAGENTA, BLACK));

	Image el = ImageFromImage(uiPng, uiElem);
	if (!IsImageReady(el)) {
		UnloadImage(uiPng);
		return LoadTextureFromImage(GenImageChecked(width, height, 2, 2, MAGENTA, BLACK));
	}

	ImageResizeNN(&el, (int)width, (int)height);
	Texture2D texture = LoadTextureFromImage(el);
	if (!IsTextureReady(texture)) {
		UnloadImage(el);
		UnloadImage(uiPng);
		return LoadTextureFromImage(GenImageChecked(width, height, 2, 2, MAGENTA, BLACK));
	}

	UnloadImage(el);
	UnloadImage(uiPng);
	return texture;
}