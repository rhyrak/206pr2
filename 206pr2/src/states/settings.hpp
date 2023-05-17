#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <raylib.h>
#include "state.hpp"
#include "../../main.hpp"

class Settings : public State
{
public:
    Settings(Config* config);
    ~Settings();
    void update() override;
    void render() override;
    int signal() override;
};

#endif
