#include "game.hpp"
#include <iostream>

game::game(state *initalState)
{
    this->_state = initalState;
}

void game::update(double delta) {
    _state->update(delta);
}