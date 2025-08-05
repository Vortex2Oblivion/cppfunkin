#include "game.hpp"
#include <iostream>

funkin::Game::Game(State *initalState)
{
    this->_state = initalState;
}

funkin::Game::~Game()
{
}

void funkin::Game::update(double delta)
{
    if (_state != nullptr)
    {
        _state->update(delta);
    }
}

void funkin::Game::switchState(State *nextState)
{
    delete _state;
    this->_state = nextState;
}