#include "timer.hpp"

#include <functional>

#include "game.hpp"

engine::Timer::Timer(const double length, const std::function<void()> &onComplete) {
    this->length = length;
    this->onComplete = onComplete;
}

engine::Timer::~Timer() = default;

void engine::Timer::start() {
    this->startTime = raylib::Window::GetTime();
    started = true;
    engine::Game::timers.push_back(*this);
}

void engine::Timer::update() {
    if (isDone()) {
        finished = true;
        onComplete();
    }
}

bool engine::Timer::isDone() const { return raylib::Window::GetTime() - startTime >= length; }
