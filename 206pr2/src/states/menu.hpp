#ifndef MENU_H
#define MENU_H

#include "state.hpp"
#include "../../main.hpp"
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
    int signal() override;
};

#endif
