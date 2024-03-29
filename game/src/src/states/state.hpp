#ifndef STATE_H
#define STATE_H

#include "../../main.hpp"

class State
{
protected:
    State(Config *config);  /*Constructor*/
    Signal signalF;
    Config* config;
public:
    virtual ~State();   /*Destructor*/
    virtual void update() = 0;  /*Overridable method*/
    virtual void render() = 0;  /*Overridable method*/
    virtual Signal signal() = 0;  /*Overridable method*/
    virtual void reset();
};

#endif
