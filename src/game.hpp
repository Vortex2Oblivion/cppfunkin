#pragma once
#include "state.hpp"

namespace funkin
{
    class Game
    {
    private:
    public:
        static void start(State *initialState);
        static void update(double delta);
        static void switchState(State *nextState);
    };

}