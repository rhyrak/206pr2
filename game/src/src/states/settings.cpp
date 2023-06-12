#include "settings.hpp"
#include "../util/GridLayout.hpp"
#include "../ui/UiElements.hpp"
#include <iostream>

inline int ROUND(float x) { return (int)(x + 0.5F); }

inline void initButtons(std::vector<IconButton*>* buttons, std::vector<Slider*>* sliders, Config* config, GridLayout* gl);

Settings::Settings(Config* config) : State(config)
{
	gl = GridLayout(config->windowWidth, config->windowHeight, -20);
	initButtons(&buttons, &sliders, config, &gl);
}

Settings::~Settings()
{
	std::cout << "****************************************************************************************************"
		"\n\t\t\tDESTRUCTING SETTINGS\n" <<
		"****************************************************************************************************\n";
	for (int i = 0; i < buttons.size(); i++)
		delete buttons.at(i);
}

int selectedId = -1;
float blinkDur = 0.5F;

void Settings::update()
{
	config->cursorType = 1;
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

		// if selected key was assigned before, remove it
		if (config->keymap.p1Up == (KeyboardKey)input && selectedId != 0)
			config->keymap.p1Up = (KeyboardKey)999;
		if (config->keymap.p1Left == (KeyboardKey)input && selectedId != 1)
			config->keymap.p1Left = (KeyboardKey)999;
		if (config->keymap.p1Down == (KeyboardKey)input && selectedId != 2)
			config->keymap.p1Down = (KeyboardKey)999;
		if (config->keymap.p1Right == (KeyboardKey)input && selectedId != 3)
			config->keymap.p1Right = (KeyboardKey)999;
		if (config->keymap.p2Up == (KeyboardKey)input && selectedId != 4)
			config->keymap.p2Up = (KeyboardKey)999;
		if (config->keymap.p2Left == (KeyboardKey)input && selectedId != 5)
			config->keymap.p2Left = (KeyboardKey)999;
		if (config->keymap.p2Down == (KeyboardKey)input && selectedId != 6)
			config->keymap.p2Down = (KeyboardKey)999;
		if (config->keymap.p2Right == (KeyboardKey)input && selectedId != 7)
			config->keymap.p2Right = (KeyboardKey)999;

		if (shouldUpdateButtons) {
			selectedId = -1;
			initButtons(&buttons, &sliders, config, &gl);
		}
	}

	blinkDur -= GetFrameTime();
	if (blinkDur <= -0.5F)
	{
		blinkDur = 0.5F;
	}

	if (config->isUpdated)
	{
		gl.recalculate(config->windowWidth, config->windowHeight);
		initButtons(&buttons, &sliders, config, &gl);
	}
}

void Settings::render()
{
	ClearBackground(UI_DARK_BROWN);
	DrawRectangle(0, 0, config->windowWidth, config->windowHeight, Color{255,255,255,96});

	for (int i = 0; i < sliders.size(); i++)
	{
		int feedback = sliders.at(i)->render();
		if (feedback == 1)
			config->cursorType = 0;
	}

	for (int i = 0; i < buttons.size(); i++)
	{
		int feedback = buttons.at(i)->render();
		if (feedback == 2)
		{
			if (i == buttons.size()-1)
				signalF = S_NAV_POP;
			else
				selectedId = i;
		}
		else if (feedback == 1)
			config->cursorType = 0;
	}
	if (selectedId >= 0 && selectedId <= 7) {
		if (blinkDur > 0)
		{
			Rectangle hb = buttons.at(selectedId)->getHitbox();
			DrawRectangle(ROUND(hb.x), ROUND(hb.y), ROUND(hb.width), ROUND(hb.height), Color{ 151,113,74,65 });
		}
	}

	DrawText("Music", ROUND(gl.getXCoord(6.75F)), ROUND(gl.getYCoord(2.4F)), ROUND(gl.getGridSize() * 0.5F), UI_DARK_BROWN);
	DrawText(" SFX", ROUND(gl.getXCoord(6.75F)), ROUND(gl.getYCoord(3.65F)), ROUND(gl.getGridSize() * 0.5F), UI_DARK_BROWN);
	DrawText("Player 1", ROUND(gl.getXCoord(7)), ROUND(gl.getYCoord(7.2F)), ROUND(gl.getGridSize() * 0.5F), UI_DARK_BROWN);
	DrawText("Player 2", ROUND(gl.getXCoord(11)), ROUND(gl.getYCoord(7.2F)), ROUND(gl.getGridSize() * 0.5F), UI_DARK_BROWN);
}

Signal Settings::signal()
{
	return signalF;
}

inline void initButtons(std::vector<IconButton*>* buttons, std::vector<Slider*>* sliders, Config* config, GridLayout *gl)
{
	for (int i = 0; i < sliders->size(); i++)
	{
		delete sliders->at(i);
	}
	sliders->clear();
	for (int i = 0; i < buttons->size(); i++)
	{
		delete buttons->at(i);
	}
	buttons->clear();

	sliders->push_back(new Slider(Rectangle{ gl->getXCoord(8.5), gl->getYCoord(2.5), gl->getGridSize() * 3,0 }, &config->musicLevel));
	sliders->push_back(new Slider(Rectangle{ gl->getXCoord(8.5), gl->getYCoord(3.75), gl->getGridSize() * 3,0 }, &config->sfxLevel));

	buttons->push_back(new IconButton(Rectangle{
		gl->getXCoord(7.5),gl->getYCoord(5),gl->getGridSize(),gl->getGridSize() }, config->keymap.p1Up));
	buttons->push_back(new IconButton(Rectangle{
		gl->getXCoord(6.5),gl->getYCoord(6),gl->getGridSize(),gl->getGridSize() }, config->keymap.p1Left));
	buttons->push_back(new IconButton(Rectangle{
		gl->getXCoord(7.5),gl->getYCoord(6),gl->getGridSize(),gl->getGridSize() }, config->keymap.p1Down));
	buttons->push_back(new IconButton(Rectangle{
		gl->getXCoord(8.5),gl->getYCoord(6),gl->getGridSize(),gl->getGridSize() }, config->keymap.p1Right));

	buttons->push_back(new IconButton(Rectangle{
		gl->getXCoord(11.5),gl->getYCoord(5),gl->getGridSize(),gl->getGridSize() }, config->keymap.p2Up));
	buttons->push_back(new IconButton(Rectangle{
		gl->getXCoord(10.5),gl->getYCoord(6),gl->getGridSize(),gl->getGridSize() }, config->keymap.p2Left));
	buttons->push_back(new IconButton(Rectangle{
		gl->getXCoord(11.5),gl->getYCoord(6),gl->getGridSize(),gl->getGridSize() }, config->keymap.p2Down));
	buttons->push_back(new IconButton(Rectangle{
		gl->getXCoord(12.5),gl->getYCoord(6),gl->getGridSize(),gl->getGridSize() }, config->keymap.p2Right));
	buttons->push_back(new IconButton(Rectangle{
		gl->getXCoord(0.5F),gl->getYCoord(0.5F),gl->getGridSize(),gl->getGridSize() }, I_ARROW_BACK));
}

void Settings::reset()
{

}
