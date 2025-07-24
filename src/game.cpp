#include "game.hpp"
#include <iostream>

game::game(state *initalState)
{
    this->_state = initalState;
}

void game::update(double delta)
{
    if (_state != nullptr)
    {
        _state->update(delta);
    }
}

void game::switchState(state *nextState)
{
    delete _state;
    this->_state = nextState;
}