#include "menu.hpp"

Menu::Menu(Config *config) : State(config)
{
	iButtons = std::vector<IconButton*>(3);
	iButtons.at(0) = new IconButton(Rectangle{ 32,32,64,64 }, I_EXIT, RED);
	iButtons.at(1) = new IconButton(Rectangle{ 112,32,64,64 }, I_GO_FULLSCREEN);
	iButtons.at(2) = new IconButton(Rectangle{ 112,32,64,64 }, I_GO_WINDOWED);
}

Menu::~Menu()
{
	for (int i = 0; i < iButtons.size(); i++)
		delete iButtons.at(i);
}

void Menu::update()
{
	signalF = S_NO_CHANGE;
	config->cursorType = 1;
	if (IsKeyPressed(KEY_P)) signalF = S_NAV_INGAME;
	if (IsKeyPressed(KEY_O)) signalF = S_NAV_SETTINGS;
}

void Menu::render()
{
	int width = config->windowWidth, height = config->windowHeight;
	DrawRectangle(0, 0, width, height, RAYWHITE);

	int exitBtn = iButtons.at(0)->render();
	if (exitBtn == 2) signalF = S_WIN_CLOSE;
	else if (exitBtn == 1) config->cursorType = 0;

	int toggleFsBtn = iButtons.at(config->isFullscreen ? 2 : 1)->render();
	if (toggleFsBtn == 2) signalF = S_WIN_TOGGLE_FS;
	else if (toggleFsBtn == 1) config->cursorType = 0;

	DrawText("Press P to play", width / 2 - 100, height / 3, 32, ORANGE);
}

Signal Menu::signal()
{
	return signalF;
}