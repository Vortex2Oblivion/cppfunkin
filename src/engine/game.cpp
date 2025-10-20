#include "game.hpp"
#include "camera.hpp"
#include <cstdio>
#include <iostream>
#include "sprite.hpp"

engine::State *engine::Game::_state = nullptr;
engine::Camera *engine::Game::defaultCamera = new engine::Camera();
std::vector<engine::Camera *> engine::Game::cameras = {engine::Game::defaultCamera};

void engine::Game::start(State *initialState)
{
    _state = initialState;
    _state->create();
}

void engine::Game::update(float delta)
{

    if (!_state->initalized)
    {
        return;
    }
    _state->update(delta);
    for (auto camera : engine::Game::cameras)
    {
        if (camera == nullptr)
        {
            continue;
        }
        camera->BeginMode();
        for (auto member : _state->members)
        {
            if (!member->alive || member->camera != camera || member == nullptr)
            {
                continue;
            }
            member->draw();
        }
        camera->EndMode();
    }
}

void engine::Game::switchState(State *nextState)
{
    engine::Sprite::clearTextureCache();
    for (auto camera : cameras)
    {
        delete camera;
    }
    defaultCamera = new engine::Camera();
    cameras = {defaultCamera};
    _state->alive = false;
    delete _state;
    _state = nextState;
    _state->create();
}
