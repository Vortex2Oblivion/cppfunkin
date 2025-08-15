#include "game.hpp"
#include <iostream>

funkin::State *funkin::Game::_state = nullptr;
raylib::Camera2D *funkin::Game::defaultCamera = new raylib::Camera2D(raylib::Vector2(0, 0), raylib::Vector2(0, 0), 0.0f, 1.0f);
std::vector<raylib::Camera2D *> funkin::Game::cameras = {funkin::Game::defaultCamera};

void funkin::Game::start(State *initialState)
{
    _state = initialState;
}

void funkin::Game::update(double delta)
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
