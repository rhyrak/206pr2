#include "menu.h"
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
	if(IsKeyPressed(KEY_P)) signalF = 2;
}

void Menu::render()
{
	int width = config->windowWidth, height = config->windowHeight;
	DrawRectangle(0, 0, width, height, RAYWHITE);
	
	signalF = -1;
	if (iButtons.at(0).render()) signalF = 69;
	if (config->isFullscreen)
	{
		if (iButtons.at(2).render()) signalF = 100;
	}
	else
	{
		if (iButtons.at(1).render()) signalF = 100;
	}

	DrawText("Press P to play", width/2 - 100, height/3, 32, ORANGE);
}

char Menu::signal()
{
	return signalF;
}