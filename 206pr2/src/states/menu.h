#ifndef MENU_H
#define MENU_H

#include "state.h"
#include "../../main.h"

class Menu : public State
{
public:
    Menu(Config *config);
    void update() override;
    void render() override;
    char signal() override;
};

#endif
