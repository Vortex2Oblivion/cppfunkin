#include "game.hpp"

static funkin::State *_state = nullptr;
std::vector<raylib::Camera2D *> cameras = {new raylib::Camera2D(raylib::Vector2(0, 0), raylib::Vector2(0, 0), 1)};

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
            camera->rotation = 45;
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
