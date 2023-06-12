#include "state.hpp"
#include "../../main.hpp"

State::State(Config *config)
{
	this->config = config;
	this->signalF = S_NO_CHANGE;
}

State::~State()
{
}

void State::reset()
{

}

void State::update()
{

}

void State::render()
{

}

Signal State::signal()
{
	return signalF;
}