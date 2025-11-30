#include "conductor.hpp"
#include <raylib-cpp.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>


funkin::Conductor::Conductor(const std::vector<std::shared_ptr<raylib::Music>> &tracks) { this->tracks = tracks; }

funkin::Conductor::~Conductor() {
    if (tracks.empty()) {
        return;
    }
    stop();
    tracks.clear();
}

void funkin::Conductor::start(std::vector<std::shared_ptr<raylib::Music>> tracks) {
    this->tracks = std::move(tracks);
    start();
}

void funkin::Conductor::start() const {
    if (tracks.empty()) {
        return;
    }
    for (const auto& track : tracks) {
        track->Play();
    }
}

void funkin::Conductor::stop() const {
    if (tracks.empty()) {
        return;
    }
    for (const auto& track : tracks) {
        track->Stop();
    }
}

void funkin::Conductor::update(const float delta) {
    if (tracks.empty()) {
        return;
    }
    for (const auto& track : tracks)
    {
        track->Update();
    }
    const auto track = tracks[0];
    // TODO MAKE THIS IN GAME OPTION RATHER THAN __APPLE__ lol
    #if __APPLE__
    if (track->GetTimePlayed() * 1000.0f >= time || abs(time - track->GetTimePlayed() * 1000.0f) > 20.0f / 1000.0f)
    #else
    if (track->GetTimePlayed() * 1000.0f != lastAudioTime)
    #endif
    {
        time = track->GetTimePlayed() * 1000.0f;
    }
    else if (track->IsPlaying())
    {
        time += delta * 1000.0f;
    }
    lastAudioTime = track->GetTimePlayed() * 1000.0f;

    const int oldStep = step;
    const int oldBeat = beat;

    updateStep();
    updateBeat();

    if (oldStep != step) {
        stepHit();
    }

    if (oldBeat != beat) {
        beatHit();
    }
}

int funkin::Conductor::getBeat() const { return beat; }

int funkin::Conductor::getStep() const { return step; }

float funkin::Conductor::getCrochet() const {
    return (60.0f / bpm) * 1000.0f;
}

float funkin::Conductor::getStepCrochet() const { return getCrochet() / 4; }

void funkin::Conductor::updateStep() {
    const int potentialNewStep = static_cast<int>(time / getCrochet());
    if (potentialNewStep != step) {
        step = potentialNewStep;
    }
}

void funkin::Conductor::updateBeat() {
    const int potentialNewBeat = static_cast<int>(time / getCrochet());
    if (potentialNewBeat != beat) {
        beat = potentialNewBeat;
    }
}

void funkin::Conductor::stepHit() {}

void funkin::Conductor::beatHit() {}

float funkin::Conductor::getMinAudioTime() const {
    if (tracks.empty()) {
        return 0.0f;
    }
    float minAudioTime = getMaxAudioTime();
    for (const auto& track : tracks) {
        if (track->GetTimeLength() < minAudioTime) {
            minAudioTime = track->GetTimeLength();
        }
    }
    return minAudioTime;
}

float funkin::Conductor::getMaxAudioTime() const {
    if (tracks.empty()) {
        return 0.0f;
    }
    float maxAudioTime = 0.0f;
    for (const auto& track : tracks) {
        if (track->GetTimeLength() >= maxAudioTime) {
            maxAudioTime = track->GetTimeLength();
        }
    }
    return maxAudioTime;
}
