#ifndef MENU_HPP
#define MENU_HPP

#include <raylib.h>
#include "state.hpp"
#include "../../main.hpp"
#include "../ui/IconButton.hpp"
#include <vector>

class Menu : public State
{
private:
    std::vector<IconButton*> iButtons;
public:
    Menu(Config *config);
    ~Menu();
    void update() override;
    void render() override;
    int signal() override;
};

#endif
