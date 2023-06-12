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
    virtual void update();  /*Overridable method*/
    virtual void render();  /*Overridable method*/
    virtual Signal signal();  /*Overridable method*/
    virtual void reset();
};

#endif
