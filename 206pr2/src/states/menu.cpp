#include "menu.h"
#include <raylib.h>

Menu::Menu(Config *config) : State(config)
{
}

void Menu::update()
{
	if(IsKeyPressed(KEY_P)) signalF = 2;
}

void Menu::render()
{
	int width = config->windowWidth, height = config->windowHeight;
	DrawRectangle(0, 0, width, height, RAYWHITE);
	
	DrawText("Press P to play", width/2 - 100, height/3, 32, ORANGE);
}

char Menu::signal()
{
	return signalF;
}