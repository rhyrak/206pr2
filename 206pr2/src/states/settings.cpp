#include "settings.hpp"

Settings::Settings(Config* config) : State(config)
{

}

Settings::~Settings()
{

}

void Settings::update()
{
	if (IsKeyPressed(KEY_SPACE)) signalF = S_NAV_MENU;
}

void Settings::render()
{
	ClearBackground(RAYWHITE);
	DrawText("WIP. Press space", 300, 300, 32, GRAY);
}

int Settings::signal()
{
	return signalF;
}
