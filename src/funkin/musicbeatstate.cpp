#include "musicbeatstate.hpp"

funkin::MusicBeatState::MusicBeatState() : State() { conductor = new Conductor(); }

funkin::MusicBeatState::~MusicBeatState() {
    conductor->stop();
    delete conductor;
}

void funkin::MusicBeatState::create() { engine::State::create(); }

void funkin::MusicBeatState::update(float delta) {
    engine::State::update(delta);
    int lastStep = conductor->getStep();
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
