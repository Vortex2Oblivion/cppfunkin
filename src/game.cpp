#include "game.hpp"
#include "camera.hpp"
#include <iostream>

funkin::State *funkin::Game::_state = nullptr;
funkin::Camera *funkin::Game::defaultCamera = new funkin::Camera();
std::vector<funkin::Camera *> funkin::Game::cameras = {funkin::Game::defaultCamera};

void funkin::Game::start(State *initialState)
{
    _state = initialState;
}

void funkin::Game::update(float delta)
{

    _state->update(delta);
    for (auto camera : funkin::Game::cameras)
    {
        if (camera != nullptr)
        {
            camera->BeginMode();
            for (auto member : _state->members)
            {
                if(member == nullptr || !member->alive || member->camera != camera)
                {
                    continue;
                }
                member->draw();
            }
            camera->EndMode();
        }
    }
}

void funkin::Game::switchState(State *nextState)
{
    delete _state;
    _state = nextState;
}
