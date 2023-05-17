#include "menu.hpp"
#include "../ui/IconButton.hpp"
#include <raylib.h>

Menu::Menu(Config *config) : State(config)
{
	iButtons = std::vector<IconButton>(3);
	iButtons.at(0) = IconButton(Rectangle{ 32,32,64,64 }, I_EXIT, RED);
	iButtons.at(1) = IconButton(Rectangle{ 112,32,64,64 }, I_GO_FULLSCREEN);
	iButtons.at(2) = IconButton(Rectangle{ 112,32,64,64 }, I_GO_WINDOWED);
}

void Menu::update()
{
	signalF = -1;
	config->cursorType = 1;
	if (IsKeyPressed(KEY_P)) signalF = 2;
}

void Menu::render()
{
	int width = config->windowWidth, height = config->windowHeight;
	DrawRectangle(0, 0, width, height, RAYWHITE);

	int exitBtn = iButtons.at(0).render();
	if (exitBtn == 2) signalF = 69;
	else if (exitBtn == 1) config->cursorType = 0;

	int toggleFsBtn = iButtons.at(config->isFullscreen ? 2 : 1).render();
	if (toggleFsBtn == 2) signalF = 100;
	else if (toggleFsBtn == 1) config->cursorType = 0;

	DrawText("Press P to play", width / 2 - 100, height / 3, 32, ORANGE);
}

int Menu::signal()
{
	return signalF;
}