#include "musicbeatstate.hpp"

#include <iostream>

funkin::MusicBeatState::MusicBeatState() : State() { conductor = std::make_shared<funkin::Conductor>(); }

funkin::MusicBeatState::~MusicBeatState() {
    conductor->stop();
}

void funkin::MusicBeatState::create() { engine::State::create(); }

void funkin::MusicBeatState::update(const float delta) {
    engine::State::update(delta);
    const int lastStep = conductor->getStep();
    conductor->update(delta);
    if (lastStep != conductor->getStep()) {
        stepHit();
    }
}

void funkin::MusicBeatState::stepHit() {
    if (conductor->getStep() % 4 == 0) {
        beatHit();
    }
}

void funkin::MusicBeatState::beatHit() {}
