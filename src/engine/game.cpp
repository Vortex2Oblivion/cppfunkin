#include "game.hpp"
#include "camera.hpp"
#include <iostream>

engine::State *engine::Game::_state = nullptr;
engine::Camera *engine::Game::defaultCamera = new engine::Camera();
std::vector<engine::Camera *> engine::Game::cameras = {engine::Game::defaultCamera};

void engine::Game::start(State *initialState)
{
    _state = initialState;
}

void engine::Game::update(float delta)
{

    _state->update(delta);
    for (auto camera : engine::Game::cameras)
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

void engine::Game::switchState(State *nextState)
{
    delete _state;
    _state = nextState;
}
