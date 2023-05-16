#ifndef STATE_H
#define STATE_H

#include "../../main.hpp"

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
    virtual int signal() = 0;  /*Overridable method*/
};

#endif