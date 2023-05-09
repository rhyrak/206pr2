#ifndef STATE_H
#define STATE_H

#include "../../main.h"

class State
{
protected:
    State(Config *config);
    char signalF;
    Config* config;
public:
    ~State();
    virtual void update() = 0;
    virtual void render() = 0;
    virtual char signal() = 0;
};

#endif
