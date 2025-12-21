#include "game.hpp"

#include "camera.hpp"
#include "sprite.hpp"

std::unique_ptr<engine::State> engine::Game::_state = nullptr;
std::shared_ptr<engine::Camera> engine::Game::defaultCamera = std::make_shared<engine::Camera>();
std::vector<std::shared_ptr<engine::Camera>> engine::Game::cameras = {engine::Game::defaultCamera};
std::vector<engine::Timer> engine::Game::timers = {};

void engine::Game::start(std::unique_ptr<State> initialState) {
    _state = std::move(initialState);
    _state->create();
}

void engine::Game::add(const std::shared_ptr<engine::Object> &obj) {
    _state->add(obj);
}

void engine::Game::update(const float delta) {
    if (_state->initialized && _state->alive) {
	    _state->update(delta);
    }
    for (const auto& camera : engine::Game::cameras) {
        if (camera == nullptr) {
            continue;
        }
        camera->BeginMode();
        for (const auto& member : _state->members) {
            if (!member->alive || member->camera != camera) {
                continue;
            }
            member->draw();
        }
        camera->EndMode();
    }
    for (auto timer : timers) {
        timer.update();
    }
    const auto timerToRemove = std::ranges::find_if(timers, [](const auto& t) { return t.isDone(); });
    timers.erase(timerToRemove, timers.end());
}

void engine::Game::switchState(std::unique_ptr<State> nextState) {
    _state->alive = false;
	_state->initialized = false;
    engine::Sprite::clearTextureCache();
    timers.clear();
    cameras.clear();
    defaultCamera = std::make_shared<engine::Camera>();
    cameras = {defaultCamera};
    _state = std::move(nextState);
    _state->create();
}
