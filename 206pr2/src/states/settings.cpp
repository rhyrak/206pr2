#include "settings.hpp"

_inline void initButtons(std::vector<IconButton*>* buttons, Config* config);

Settings::Settings(Config* config) : State(config)
{
	initButtons(&buttons, config);
}

Settings::~Settings()
{

}

int selectedId = -1;
float blinkDur = 0.5F;

void Settings::update()
{
	config->cursorType = 1;
	if (IsKeyPressed(KEY_SPACE)) signalF = S_NAV_MENU;
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) selectedId = -1;
	int input = GetKeyPressed();
	bool shouldUpdateButtons = false;
	if ((input >= KEY_A && input <= KEY_Z) ||
		(input >= KEY_ZERO && input <= KEY_NINE) ||
		(input >= KEY_RIGHT && input <= KEY_UP))
	{
		switch (selectedId)
		{
		case 0: config->keymap.p1Up = (KeyboardKey)input; shouldUpdateButtons = true; break;
		case 1: config->keymap.p1Left = (KeyboardKey)input; shouldUpdateButtons = true; break;
		case 2: config->keymap.p1Down = (KeyboardKey)input; shouldUpdateButtons = true; break;
		case 3: config->keymap.p1Right = (KeyboardKey)input; shouldUpdateButtons = true; break;
		case 4: config->keymap.p2Up = (KeyboardKey)input; shouldUpdateButtons = true; break;
		case 5: config->keymap.p2Left = (KeyboardKey)input; shouldUpdateButtons = true; break;
		case 6: config->keymap.p2Down = (KeyboardKey)input; shouldUpdateButtons = true; break;
		case 7: config->keymap.p2Right = (KeyboardKey)input; shouldUpdateButtons = true; break;
		}

		if (shouldUpdateButtons) {
			selectedId = -1;
			initButtons(&buttons, config);
		}
	}

	blinkDur -= GetFrameTime();
	if (blinkDur <= -0.5F)
	{
		blinkDur = 0.5F;
	}
}

void Settings::render()
{
	ClearBackground(RAYWHITE);
	DrawText("WIP. Press space to go back", 300, 300, 32, GRAY);
	for (int i = 0; i < buttons.size(); i++)
	{
		int feedback = buttons.at(i)->render();
		if (feedback == 2)
			selectedId = i;
		else if (feedback == 1)
			config->cursorType = 0;
	}
	if (selectedId >= 0 && selectedId <= 7) {
		if (blinkDur > 0)
		{
			Rectangle hb = buttons.at(selectedId)->getHitbox();
			DrawRectangle(hb.x, hb.y, hb.width, hb.height, Color{ 25,137,184,65 });
		}
	}

	DrawText("Player 1", 315, 500, 32, Color{ 25,137,184,255 });
	DrawText("Player 2", 615, 500, 32, Color{ 25,137,184,255 });
}

int Settings::signal()
{
	return signalF;
}


_inline void initButtons(std::vector<IconButton*>* buttons, Config* config)
{
	for (int i = 0; i < buttons->size(); i++)
	{
		delete buttons->at(i);
	}
	buttons->clear();

	buttons->push_back(new IconButton(Rectangle{ 350,350,64,64 }, config->keymap.p1Up));
	buttons->push_back(new IconButton(Rectangle{ 350 - 70,350 + 70,64,64 }, config->keymap.p1Left));
	buttons->push_back(new IconButton(Rectangle{ 350,350 + 70,64,64 }, config->keymap.p1Down));
	buttons->push_back(new IconButton(Rectangle{ 350 + 70,350 + 70,64,64 }, config->keymap.p1Right));

	buttons->push_back(new IconButton(Rectangle{ 650,350,64,64 }, config->keymap.p2Up));
	buttons->push_back(new IconButton(Rectangle{ 650 - 70,350 + 70,64,64 }, config->keymap.p2Left));
	buttons->push_back(new IconButton(Rectangle{ 650,350 + 70,64,64 }, config->keymap.p2Down));
	buttons->push_back(new IconButton(Rectangle{ 650 + 70,350 + 70,64,64 }, config->keymap.p2Right));
}