#pragma once
#include "state.hpp"

namespace funkin
{
    class Game
    {
    private:
        /* data */
        State *_state;

    public:
        Game(State *initalState);
        ~Game();
        void update(double delta);
        void switchState(State *nextState);
    };

}