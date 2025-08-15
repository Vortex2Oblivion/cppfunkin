#pragma once
#include "state.hpp"

namespace funkin
{
    class Game
    {
    private:
        static funkin::State *_state;

    public:
        static void start(State *initialState);
        static void update(double delta);
        static void switchState(State *nextState);
        static std::vector<raylib::Camera2D *> cameras;
        static raylib::Camera2D *defaultCamera;
    };

}