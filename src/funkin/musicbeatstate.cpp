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
    const int lastBeat = conductor->getBeat();
    conductor->update(delta);
    if (lastStep != conductor->getStep()) {
        stepHit();
    }
    if (lastBeat != conductor->getBeat()) {
        beatHit();
    }
}

void funkin::MusicBeatState::stepHit() {

}

void funkin::MusicBeatState::beatHit() {}
