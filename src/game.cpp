#include "game.hpp"

static funkin::State *_state = nullptr;

void funkin::Game::start(State *initialState)
{
    _state = initialState;
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
    _state = nextState;
}
