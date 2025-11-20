#include "musicbeatstate.hpp"

#include <iostream>

funkin::MusicBeatState::MusicBeatState() = default;

funkin::MusicBeatState::~MusicBeatState() {
    conductor->stop();
}

void funkin::MusicBeatState::create() {
    conductor = std::make_shared<funkin::Conductor>();
    engine::State::create();
}

void funkin::MusicBeatState::update(const float delta) {
    engine::State::update(delta);
    const int lastStep = conductor->getStep();
    const int lastBeat = conductor->getBeat();
    conductor->update(delta);
    if (lastStep != conductor->getStep() || forceConductorUpdate) {
        stepHit();
    }
    if (lastBeat != conductor->getBeat() || forceConductorUpdate) {
        beatHit();
    }
    forceConductorUpdate = false;
}

void funkin::MusicBeatState::stepHit() {

}

void funkin::MusicBeatState::beatHit() {}
