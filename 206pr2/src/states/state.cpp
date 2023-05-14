#include "state.hpp"
#include "../../main.hpp"

State::State(Config *config)
{
	this->config = config;
	this->signalF = -1;
}

State::~State()
{
}