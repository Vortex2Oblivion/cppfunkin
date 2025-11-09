#include "game.hpp"

#include <cstdio>
#include <iostream>

#include "camera.hpp"
#include "sprite.hpp"

std::unique_ptr<engine::State> engine::Game::_state = nullptr;
engine::Camera* engine::Game::defaultCamera = new engine::Camera();
std::vector<engine::Camera*> engine::Game::cameras = {engine::Game::defaultCamera};

engine::Game::Game(std::unique_ptr<State> initialState) {
    _state = std::move(initialState);
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

void engine::Game::switchState(std::unique_ptr<State> nextState) {
    engine::Sprite::clearTextureCache(false);
    for (const auto camera : cameras) {
        delete camera;
    }
    defaultCamera = new engine::Camera();
    cameras = {defaultCamera};
    _state->alive = false;
    _state = std::move(nextState);
    _state->create();
}
