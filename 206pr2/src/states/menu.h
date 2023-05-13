#ifndef MENU_H
#define MENU_H

#include "state.h"
#include "../../main.h"
#include "../ui/IconButton.hpp"
#include <vector>

class Menu : public State
{
private:
    std::vector<IconButton> iButtons;
public:
    Menu(Config *config);
    void update() override;
    void render() override;
    char signal() override;
};

#endif
