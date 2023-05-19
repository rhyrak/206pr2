#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <raylib.h>
#include "state.hpp"
#include "../../main.hpp"
#include "../ui/IconButton.hpp"

class Settings : public State
{
private:
    std::vector<IconButton*> buttons;
public:
    Settings(Config* config);
    ~Settings();
    void update() override;
    void render() override;
    Signal signal() override;
};

#endif
