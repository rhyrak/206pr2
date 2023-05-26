#include "UiElements.hpp"

#define ROUND(x) ((int)(x+0.5F))

Texture2D getTexture(UiElement uiElem, float scale) {
	Image uiPng = LoadImage("res/ui/ui.png");
	if (!IsImageReady(uiPng) || uiElem.width == 0 || uiElem.height == 0)
		return LoadTextureFromImage(GenImageChecked(ROUND(16 * scale), ROUND(16 * scale), ROUND(16 * scale), ROUND(16 * scale), MAGENTA, BLACK));

	Image el = ImageFromImage(uiPng, uiElem);
	if (!IsImageReady(el)) {
		UnloadImage(uiPng);
		return LoadTextureFromImage(GenImageChecked(ROUND(16 * scale), ROUND(16 * scale), ROUND(16 * scale), ROUND(16 * scale), MAGENTA, BLACK));
	}

	ImageResizeNN(&el, ROUND(el.width * scale), ROUND(el.height * scale));
	Texture2D texture = LoadTextureFromImage(el);
	if (!IsTextureReady(texture)) {
		UnloadImage(el);
		UnloadImage(uiPng);
		return LoadTextureFromImage(GenImageChecked(ROUND(16 * scale), ROUND(16 * scale), ROUND(16 * scale), ROUND(16 * scale), MAGENTA, BLACK));
	}

	UnloadImage(el);
	UnloadImage(uiPng);
	return texture;
}


Texture2D getTexture(UiElement uiElem, float width, float height) {
	Image uiPng = LoadImage("res/ui/ui.png");
	if (!IsImageReady(uiPng) || uiElem.width == 0 || uiElem.height == 0)
		return LoadTextureFromImage(GenImageChecked(ROUND(width), ROUND(height), 2, 2, MAGENTA, BLACK));

	Image el = ImageFromImage(uiPng, uiElem);
	if (!IsImageReady(el)) {
		UnloadImage(uiPng);
		return LoadTextureFromImage(GenImageChecked(ROUND(width), ROUND(height), 2, 2, MAGENTA, BLACK));
	}

	ImageResizeNN(&el, ROUND(width), ROUND(height));
	Texture2D texture = LoadTextureFromImage(el);
	if (!IsTextureReady(texture)) {
		UnloadImage(el);
		UnloadImage(uiPng);
		return LoadTextureFromImage(GenImageChecked(ROUND(width), ROUND(height), 2, 2, MAGENTA, BLACK));
	}

	UnloadImage(el);
	UnloadImage(uiPng);
	return texture;
}