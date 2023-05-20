#ifndef MENU_HPP
#define MENU_HPP

#include <raylib.h>
#include "state.hpp"
#include "../../main.hpp"
#include "../ui/IconButton.hpp"
#include "../ui/Button.hpp"
#include <vector>
#include "../util/GridLayout.hpp"

class Menu : public State
{
private:
    std::vector<IconButton*> iButtons; // Icon buttons
    std::vector<Button*> mButtons; // Menu buttons
    Texture2D background;
    GridLayout gl;
public:
    Menu(Config *config);
    ~Menu();
    void update() override;
    void render() override;
    Signal signal() override;
};

#endif
