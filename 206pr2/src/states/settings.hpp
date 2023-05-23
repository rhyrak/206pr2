#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <raylib.h>
#include "state.hpp"
#include "../../main.hpp"
#include "../ui/IconButton.hpp"
#include "../ui/Slider.hpp"
#include "../util/GridLayout.hpp"

class Settings : public State
{
private:
    std::vector<IconButton*> buttons;
    std::vector<Slider*> sliders;
    GridLayout gl;
public:
    Settings(Config* config);
    ~Settings();
    void update() override;
    void render() override;
    Signal signal() override;
};

#endif
