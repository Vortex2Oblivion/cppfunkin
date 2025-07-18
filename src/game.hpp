#pragma once
#include "state.hpp"

class game
{
private:
    /* data */
    state *_state;

public:
    game(state *initalState);
    ~game();
    void update(double delta);
};
