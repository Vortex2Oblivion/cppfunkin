#include "game.hpp"

funkin::State *funkin::Game::_state = nullptr;
raylib::Camera2D *funkin::Game::defaultCamera = new raylib::Camera2D(raylib::Vector2(0, 0), raylib::Vector2(0, 0), 0);
std::vector<raylib::Camera2D *> funkin::Game::cameras = {funkin::Game::defaultCamera};

void funkin::Game::start(State *initialState)
{
    _state = initialState;
}

void funkin::Game::update(double delta)
{
    for (auto camera : cameras)
    {
        if (camera != nullptr)
        {
            camera->BeginMode();
        }
    }
    if (_state != nullptr)
    {
        _state->update(delta);
    }
    for (auto camera : cameras)
    {
        if (camera != nullptr)
        {
            camera->EndMode();
        }
    }
}

void funkin::Game::switchState(State *nextState)
{
    delete _state;
    _state = nextState;
}
