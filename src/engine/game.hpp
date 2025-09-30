#pragma once
#include "state.hpp"
#include "camera.hpp"

namespace engine
{
    class Game
    {
    private:
        static engine::State *_state;

    public:
        static void start(State *initialState);
        static void update(float delta);
        static void switchState(State *nextState);
        static std::vector<engine::Camera *> cameras;
        static engine::Camera *defaultCamera;
    };

}