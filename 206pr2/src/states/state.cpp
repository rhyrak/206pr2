#include "state.h"
#include "../../main.h"

State::State(Config *config)
{
	this->config = config;
	this->signalF = -1;
}

State::~State()
{
}