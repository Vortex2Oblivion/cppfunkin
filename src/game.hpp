#pragma once
#include "state.hpp"
#include "camera.hpp"

namespace funkin
{
    class Game
    {
    private:
        static funkin::State *_state;

    public:
        static void start(State *initialState);
        static void update(float delta);
        static void switchState(State *nextState);
        static std::vector<funkin::Camera *> cameras;
        static funkin::Camera *defaultCamera;
    };

}