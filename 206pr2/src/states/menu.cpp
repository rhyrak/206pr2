#include "menu.hpp"

inline void initButtons(Config* config, GridLayout* gl, std::vector<IconButton*> *iBtns, std::vector<Button*> *mBtns, Texture2D *bg);

Menu::Menu(Config *config) : State(config)
{
	gl = GridLayout(config->windowWidth, config->windowHeight, -25);
	initButtons(config, &gl, &iButtons, &mButtons, &background);
}

Menu::~Menu()
{
	for (int i = 0; i < iButtons.size(); i++)
		delete iButtons.at(i);

	for (int i = 0; i < mButtons.size(); i++)
		delete mButtons.at(i);

	UnloadTexture(background);
}

void Menu::update()
{
	signalF = S_NO_CHANGE;
	config->cursorType = 1;
	if (IsKeyPressed(KEY_P)) signalF = S_NAV_INGAME;
	if (IsKeyPressed(KEY_O)) signalF = S_NAV_SETTINGS;
	if (config->isUpdated)
	{
		gl.recalculate(config->windowWidth, config->windowHeight);
		initButtons(config, &gl, &iButtons, &mButtons, &background);
	}
}

void Menu::render()
{
	int width = config->windowWidth, height = config->windowHeight;
	ClearBackground(RAYWHITE);
	DrawTexture(background, 0, 0, WHITE);
	//gl.drawGrid();

	int toggleFsBtn = iButtons.at(config->isFullscreen ? 1 : 0)->render();
	if (toggleFsBtn == 2) signalF = S_WIN_TOGGLE_FS;
	else if (toggleFsBtn == 1) config->cursorType = 0;

	for (int i = 0; i < mButtons.size(); i++)
	{
		int feedback = mButtons.at(i)->render();
		if (feedback == 1) config->cursorType = 0;
		else if (feedback == 2) {
			switch (i)
			{
			case 0: signalF = S_NAV_INGAME; break;
			case 1: signalF = S_NAV_SETTINGS; break;
			case 2: signalF = S_WIN_CLOSE; break;
			}
		}
	}
}

Signal Menu::signal()
{
	return signalF;
}

inline void initButtons(Config* config, GridLayout* gl, std::vector<IconButton*>* iBtns, std::vector<Button*>* mBtns, Texture2D *bg)
{
	for (int i = 0; i < iBtns->size(); i++)
		delete iBtns->at(i);
	for (int i = 0; i < mBtns->size(); i++)
		delete mBtns->at(i);

	UnloadTexture(*bg);
	Image temp = LoadImage("res/ui/menu.png");
	ImageResizeNN(&temp, config->windowWidth, config->windowHeight);
	*bg = LoadTextureFromImage(temp);

	*iBtns = std::vector<IconButton*>(2);
	iBtns->at(0) = new IconButton(Rectangle{ gl->getXCoord(0.5),gl->getYCoord(0.5),gl->getGridSize(),gl->getGridSize() }, I_GO_FULLSCREEN);
	iBtns->at(1) = new IconButton(Rectangle{ gl->getXCoord(0.5),gl->getYCoord(0.5),gl->getGridSize(),gl->getGridSize() }, I_GO_WINDOWED);

	*mBtns = std::vector<Button*>(3);
	mBtns->at(0) = new Button(Rectangle(Rectangle{ gl->getXCoord(10),gl->getYCoord(4),5*gl->getGridSize(),1.5F*gl->getGridSize() }), "PLAY", gl->getGridSize()*0.75F);
	mBtns->at(1) = new Button(Rectangle(Rectangle{ gl->getXCoord(10),gl->getYCoord(6),5*gl->getGridSize(),1.5F*gl->getGridSize() }), "SETTINGS", gl->getGridSize()*0.55F);
	mBtns->at(2) = new Button(Rectangle(Rectangle{ gl->getXCoord(10),gl->getYCoord(8),5*gl->getGridSize(),1.5F*gl->getGridSize() }), "EXIT", gl->getGridSize()*0.75F);
}
