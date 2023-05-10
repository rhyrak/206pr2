#ifndef STATE_H
#define STATE_H

#include "../../main.h"

class State
{
protected:
    State(Config *config);  /*Constructor*/
    char signalF;
    Config* config;
public:
    ~State();   /*Destructor*/
    virtual void update() = 0;  /*Overridable method*/
    virtual void render() = 0;  /*Overridable method*/
    virtual char signal() = 0;  /*Overridable method*/
};

#endif
