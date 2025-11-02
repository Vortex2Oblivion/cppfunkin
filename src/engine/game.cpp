#include "game.hpp"

#include <cstdio>
#include <iostream>

#include "camera.hpp"
#include "sprite.hpp"

engine::State* engine::Game::_state = nullptr;
engine::Camera* engine::Game::defaultCamera = new engine::Camera();
std::vector<engine::Camera*> engine::Game::cameras = {engine::Game::defaultCamera};

void engine::Game::start(State* initialState) {
    _state = initialState;
    _state->create();
}

void engine::Game::update(const float delta) {
    if (!_state->initialized) {
        return;
    }
    _state->update(delta);
    for (const auto camera : engine::Game::cameras) {
        if (camera == nullptr) {
            continue;
        }
        camera->BeginMode();
        for (const auto member : _state->members) {
            if (!member->alive || member->camera != camera) {
                continue;
            }
            member->draw();
        }
        camera->EndMode();
    }
}

void engine::Game::switchState(State* nextState) {
    engine::Sprite::clearTextureCache();
    for (const auto camera : cameras) {
        delete camera;
    }
    defaultCamera = new engine::Camera();
    cameras = {defaultCamera};
    _state->alive = false;
    delete _state;
    _state = nextState;
    _state->create();
}
